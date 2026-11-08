#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main() {
    const char *filename = "numbers.txt";
    int fd;
    char buf[1024];

    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error creating file");
        return 1;
    }
    
    for (int i = 1; i <= 10; i++) {
        int len = snprintf(buf, sizeof(buf), "%d\n", i);
        if (write(fd, buf, len) == -1) {
            perror("Error writing initial numbers");
            close(fd);
            return 1;
        }
    }
    close(fd);

    fd = open(filename, O_RDWR);
    if (fd == -1) {
        perror("Error reopening file");
        return 1;
    }

    int newline_count = 0;
    char c;
    off_t line4_start = -1;
    
    while (read(fd, &c, 1) == 1) {
        if (c == '\n') {
            newline_count++;
            if (newline_count == 3) {
                line4_start = lseek(fd, 0, SEEK_CUR);
                break;
            }
        }
    }

    if (line4_start == (off_t)-1) {
        fprintf(stderr, "Could not find line 4\n");
        close(fd);
        return 1;
    }

    off_t remainder_start = -1;
    while (read(fd, &c, 1) == 1) {
        if (c == '\n') {
            remainder_start = lseek(fd, 0, SEEK_CUR);
            break;
        }
    }

    char remainder_buf[1024];
    ssize_t remainder_len = 0;
    
    if (remainder_start != (off_t)-1) {
        lseek(fd, remainder_start, SEEK_SET);
        remainder_len = read(fd, remainder_buf, sizeof(remainder_buf));
        if (remainder_len == -1) {
            perror("Error reading remainder");
            close(fd);
            return 1;
        }
    }

    if (lseek(fd, line4_start, SEEK_SET) == (off_t)-1) {
        perror("Error seeking to line 4 start");
        close(fd);
        return 1;
    }
    
    const char *new_text = "100\n";
    if (write(fd, new_text, strlen(new_text)) == -1) {
        perror("Error writing new text");
        close(fd);
        return 1;
    }
    
    if (remainder_len > 0) {
        if (write(fd, remainder_buf, remainder_len) == -1) {
            perror("Error writing remainder");
            close(fd);
            return 1;
        }
    }

    off_t final_size = lseek(fd, 0, SEEK_CUR);
    if (ftruncate(fd, final_size) == -1) {
        perror("Error truncating file");
        close(fd);
        return 1;
    }

    if (lseek(fd, 0, SEEK_SET) == (off_t)-1) {
        perror("Error rewinding for verification");
        close(fd);
        return 1;
    }
    
    ssize_t bytes_read;
    while ((bytes_read = read(fd, buf, sizeof(buf))) > 0) {
        if (write(STDOUT_FILENO, buf, bytes_read) == -1) {
            perror("Error writing to stdout");
            break;
        }
    }

    if (close(fd) == -1) {
        perror("Error closing file");
        return 1;
    }

    return 0;
}