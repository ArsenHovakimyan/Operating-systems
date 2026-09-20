#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("Child PID: %d exiting...\n", getpid());
        exit(0);
    } else {
        //printf("Parent PID: %d sleeping\n", getpid());
        //sleep(20);
        wait(NULL);
        printf("Parent process waiting child\n");
    }

    return 0;
}