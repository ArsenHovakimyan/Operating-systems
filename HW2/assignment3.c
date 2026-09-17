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
        execl("/bin/echo", "echo", "Hello from the child process", NULL);        
        perror("execl failed");
        exit(1);
    } else {
        wait(NULL);
        printf("Parent process done\n");
    }
    return 0;
}