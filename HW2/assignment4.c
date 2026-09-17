#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        execl("/bin/grep", "grep", "main", "test.txt", NULL);
        perror("execl failed");
        exit(1);
    } else {
        wait(NULL);
        printf("\n");
        printf("Parent process completed\n");
    }
    return 0;
}