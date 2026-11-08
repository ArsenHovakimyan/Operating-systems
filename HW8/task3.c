#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main() {
    char filepath[256];

    printf("Enter file path: ");
    if (scanf("%255s", filepath) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    int fd = open(filepath, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    off_t size = lseek(fd, 0, SEEK_END);
    if (size == (off_t)-1) {
        perror("Error seeking to end of file");
        close(fd);
        return 1;
    }

    if (size == 0) {
        write(STDOUT_FILENO, "\n", 1);
        close(fd);
        return 0;
    }

    char byte;
    for (off_t i = size - 1; i >= 0; i--) {
        if (lseek(fd, i, SEEK_SET) == (off_t)-1) {
            perror("Error seeking backward");
            break; 
        }

        if (read(fd, &byte, 1) == -1) {
            if (errno == EINTR) {
                i++; 
                continue;
            }
            perror("Error reading byte");
            break;
        }

        if (write(STDOUT_FILENO, &byte, 1) == -1) {
            perror("Error writing to stdout");
            break;
        }
    }

    write(STDOUT_FILENO, "\n", 1);

    if (close(fd) == -1) {
        perror("Error closing file");
        return 1;
    }

    return 0;
}