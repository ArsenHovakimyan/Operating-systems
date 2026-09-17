#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1 = fork();

    if (pid1 < 0) {
        perror("First fork failed");
        exit(1);
    } else if (pid1 == 0) {
        execl("/bin/ls", "ls", NULL);
        perror("execl ls failed");
        exit(1);
    }

    pid_t pid2 = fork();

    if (pid2 < 0) {
        perror("Second fork failed");
        exit(1);
    } else if (pid2 == 0) {
        execl("/bin/date", "date", NULL);
        perror("execl date failed");
        exit(1);
    }

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    
    printf("Parent process done\n");
    return 0;
}