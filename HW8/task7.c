#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main() {
    char path1[256];
    char path2[256];

    printf("Enter first file path: ");
    if (scanf("%255s", path1) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    
    printf("Enter second file path: ");
    if (scanf("%255s", path2) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    int fd1 = open(path1, O_RDONLY);
    if (fd1 == -1) {
        perror("Error opening first file");
        return 1;
    }

    int fd2 = open(path2, O_RDONLY);
    if (fd2 == -1) {
        perror("Error opening second file");
        close(fd1);
        return 1;
    }

    char buf1[4096];
    char buf2[4096];
    off_t global_offset = 0;

    while (1) {
        size_t bytes1 = 0;
        size_t bytes2 = 0;

        while (bytes1 < 4096) {
            ssize_t ret = read(fd1, buf1 + bytes1, 4096 - bytes1);
            if (ret == -1) {
                if (errno == EINTR) continue;
                perror("Error reading first file");
                close(fd1); close(fd2);
                return 1;
            }
            if (ret == 0) break;
            bytes1 += ret;
        }

        while (bytes2 < 4096) {
            ssize_t ret = read(fd2, buf2 + bytes2, 4096 - bytes2);
            if (ret == -1) {
                if (errno == EINTR) continue;
                perror("Error reading second file");
                close(fd1); close(fd2);
                return 1;
            }
            if (ret == 0) break;
            bytes2 += ret;
        }

        if (bytes1 == 0 && bytes2 == 0) {
            printf("Files are identical\n");
            close(fd1);
            close(fd2);
            return 0;
        }

        size_t min_bytes = (bytes1 < bytes2) ? bytes1 : bytes2;
        
        for (size_t i = 0; i < min_bytes; i++) {
            if (buf1[i] != buf2[i]) {
                printf("Files differ at byte %ld\n", (long)(global_offset + i));
                close(fd1);
                close(fd2);
                return 1;
            }
        }

        if (bytes1 != bytes2) {
            printf("Files differ at byte %ld\n", (long)(global_offset + min_bytes));
            close(fd1);
            close(fd2);
            return 1;
        }

        global_offset += min_bytes;
    }
    return 0;
}