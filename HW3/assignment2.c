#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2;
    int status;

    pid1 = fork();
    if (pid1 == 0) {
        printf("Child 1 PID: %d\n", getpid());
        sleep(2);
        exit(10);
    }

    pid2 = fork();
    if (pid2 == 0) {
        printf("Child 2 PID: %d\n", getpid());
        sleep(1);
        exit(20);
    }

    printf("Parent Waiting for Child 2 (PID: %d)...\n", pid2);
    waitpid(pid2, &status, 0);
    printf("Parent Child 2 finished with exit status: %d\n", WEXITSTATUS(status));


    printf("Parent Waiting for Child 1 to complete...\n");
    wait(&status);
    printf("Parent Child 1 finished with exit status: %d\n", WEXITSTATUS(status));
    return 0;
}