#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2;
    int status;

    pid1 = fork();

    if (pid1 == 0) {
        printf("Child 1 PID: %d exiting normally.\n", getpid());
        exit(0);
    }
    pid2 = fork();

    if (pid2 == 0) {
        printf("Child 2 PID: %d exiting with error code.\n", getpid());
        exit(5);
    }

    pid_t children[2] = {pid1, pid2};

    for (int i = 0; i < 2; i++) {
        waitpid(children[i], &status, 0);
        int code = WEXITSTATUS(status);
        if (code == 0) {
            printf("Child PID %d exited normally (Status: %d).\n", children[i], code);
        } else {
            printf("Child PID %d exited with ERROR code %d.\n", children[i], code);
        }   
    }
    return 0;
}