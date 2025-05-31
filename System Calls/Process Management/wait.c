#include <stdio.h>
#include <unistd.h> // Included for fork()
#include <sys/wait.h> // Included for wait()
#include <stdlib.h> // Included for exit()

int main(){

    pid_t pid = fork();

    if(pid == 0){

        // This is child process
        int childPID = getpid(); // returns the process id of current process.
        printf("This is child process with id: %d\n" , childPID);
        exit(7); // 7 gets stored where status points to. 

    }else if(pid > 0){

        // This is parent process
        // fork returns child pid in parent process.
        int parentPID = getpid();
        printf("This is parent process with id: %d and child id: %d\n", parentPID, pid);

        int status;
        pid_t childPID = waitpid(pid, &status, 0);

        // if (WIFEXITED(status)) {
        //     printf("Child %d exited with status: %d\n", childPID, WEXITSTATUS(status));
        // }

        printf("Child Execution Finished: %d\n" , status);


    }else {
        printf("Fork Failed\n");
    }

    return 0;
}
