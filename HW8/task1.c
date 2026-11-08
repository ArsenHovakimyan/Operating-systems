#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main() {
    char src_path[256];
    char dst_path[256];

    printf("Enter source file path: ");
    if (scanf("%255s", src_path) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    
    printf("Enter destination file path: ");
    if (scanf("%255s", dst_path) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    int src_fd = open(src_path, O_RDONLY);
    if (src_fd == -1) {
        perror("Error opening source file");
        return 1;
    }

    int dst_fd = open(dst_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dst_fd == -1) {
        perror("Error opening destination file");
        close(src_fd);
        return 1;
    }

    char buf[4096];
    ssize_t bytes_read;
    unsigned long total_copied = 0;
    
    int has_error = 0; 

    while (1) {
        bytes_read = read(src_fd, buf, 4096);
        
        if (bytes_read == -1) {
            if (errno == EINTR) continue;
            perror("Error reading from source");
            has_error = 1;
            break;
        }
        
        if (bytes_read == 0) {
            break;
        }

        ssize_t bytes_written = 0;
        while (bytes_written < bytes_read) {
            ssize_t ret = write(dst_fd, buf + bytes_written, bytes_read - bytes_written);

            if (ret == -1) {
                if (errno == EINTR) continue;
                perror("Error writing to destination");
                has_error = 1;
                break;
            }
            bytes_written += ret;
        }
        
        if (has_error) {
            break;
        }
        
        total_copied += bytes_read;
    }

    if (close(src_fd) == -1) perror("Error closing source file");
    if (close(dst_fd) == -1) perror("Error closing destination file");

    printf("Total bytes copied: %lu\n", total_copied);
    
    return has_error ? 1 : 0;
}