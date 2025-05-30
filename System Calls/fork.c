#include <stdio.h>
#include <unistd.h> // Included for fork()

int main(){

    pid_t pid = fork();

    if(pid == 0){

        // This is child process
        int childPID = getpid();
        printf("This is child process with id: %d\n" , childPID);

    }else if(pid > 0){

        // This is parent process
        int parentPID = getpid();
        printf("This is parent process with id: %d and child id: %d\n", parentPID, pid);

    }else {
        printf("Fork Failed\n");
    }

    return 0;
}
