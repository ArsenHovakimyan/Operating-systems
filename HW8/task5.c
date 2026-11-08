#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main() {
    const char *filename = "sparse.bin";
    int fd;
    off_t size;

    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error creating sparse.bin");
        return 1;
    }

    if (write(fd, "START", 5) == -1) {
        perror("Error writing START");
        close(fd);
        return 1;
    }

    if (lseek(fd, 1024 * 1024, SEEK_CUR) == (off_t)-1) {
        perror("Error seeking forward");
        close(fd);
        return 1;
    }

    if (write(fd, "END", 3) == -1) {
        perror("Error writing END");
        close(fd);
        return 1;
    }

    if (close(fd) == -1) {
        perror("Error closing file after writing");
        return 1;
    }

    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error reopening sparse.bin");
        return 1;
    }

    size = lseek(fd, 0, SEEK_END);
    if (size == (off_t)-1) {
        perror("Error seeking to the end");
        close(fd);
        return 1;
    }

    printf("Apparent file size: %ld bytes\n", (long)size);

    /*
     * By seeking past the end of the file and writing new data, we created a 
     * zero-padded gap called a hole. these files are known as sparse files. Holes do 
     * not occupy any physical disk space. This means a file's logical, 
     * apparent size can be much larger than the actual physical blocks it consumes on the hard drive.
     */

    if (close(fd) == -1) {
        perror("Error closing file at the end");
        return 1;
    }

    return 0;
}