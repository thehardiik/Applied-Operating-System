#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        printf("I am the child process. PID = %d\n", getpid());
    } else {
        printf("I am the parent process. PID = %d, Child PID = %d\n", getpid(), pid);
    }

    return 0;
}
