#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main() {
    const char *filename = "data.txt";
    const char *text = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int fd;
    off_t size;

    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error opening file for writing");
        return 1;
    }

    if (write(fd, text, strlen(text)) == -1) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }
    
    if (close(fd) == -1) {
        perror("Error closing file after write");
        return 1;
    }

    fd = open(filename, O_RDWR);
    if (fd == -1) {
        perror("Error reopening file");
        return 1;
    }

    size = lseek(fd, 0, SEEK_END);
    if (size == (off_t)-1) {
        perror("Error seeking to end");
        close(fd);
        return 1;
    }
    printf("Original size: %ld bytes\n", (long)size);

    if (ftruncate(fd, 10) == -1) {
        perror("Error truncating file");
        close(fd);
        return 1;
    }

    size = lseek(fd, 0, SEEK_END);
    if (size == (off_t)-1) {
        perror("Error seeking to end after truncation");
        close(fd);
        return 1;
    }
    printf("New size: %ld bytes\n", (long)size);

    if (lseek(fd, 0, SEEK_SET) == (off_t)-1) {
        perror("Error rewinding file");
        close(fd);
        return 1;
    }

    char buf[32] = {0};
    ssize_t bytes_read = read(fd, buf, sizeof(buf) - 1);
    if (bytes_read == -1) {
        perror("Error reading file");
        close(fd);
        return 1;
    }

    printf("Remaining content: %s\n", buf);

    if (close(fd) == -1) {
        perror("Error closing file at the end");
        return 1;
    }

    return 0;
}