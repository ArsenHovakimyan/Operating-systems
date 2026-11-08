#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main() {
    int fd;
    char input_buf[1024];
    char write_buf[1088];
    ssize_t bytes_read;
    pid_t pid;

    fd = open("log.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
        perror("Error opening log.txt");
        return 1;
    }

    printf("Enter a log entry: ");
    fflush(stdout); 
    bytes_read = read(STDIN_FILENO, input_buf, 1023);
    
    if (bytes_read == -1) {
        perror("Error reading from stdin");
        close(fd);
        return 1;
    }

    input_buf[bytes_read] = '\0';

    if (bytes_read > 0 && input_buf[bytes_read - 1] == '\n') {
        input_buf[bytes_read - 1] = '\0';
    }

    pid = getpid();
    int write_len = snprintf(write_buf, sizeof(write_buf), "PID=%d: %s\n", pid, input_buf);

    if (write(fd, write_buf, write_len) == -1) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }


    off_t current_offset = lseek(fd, 0, SEEK_CUR);
    if (current_offset == (off_t)-1) {
        perror("Error seeking");
        close(fd);
        return 1;
    }

    printf("New file offset: %ld bytes\n", (long)current_offset);

    if (close(fd) == -1) {
        perror("Error closing file");
        return 1;
    }

    return 0;
}