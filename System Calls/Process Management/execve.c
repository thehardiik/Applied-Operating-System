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

        char *args[] = {"/bin/ls", "-l", NULL}; // When a program runs, the first argument (argv[0]) is by convention the program’s own name or path.
        char *env[] = {NULL};


        if (execve("/bin/ls", args, env) == -1) {
            perror("execve failed");
            exit(1);  // Exit child if execve fails
        }

        exit(0);

    }else if(pid > 0){

        // This is parent process
        // fork returns child pid in parent process.
        int parentPID = getpid();
        printf("This is parent process with id: %d and child id: %d\n", parentPID, pid);

        int status;
        pid_t childPID = waitpid(pid, &status, 0);

        printf("Child Execution Finished: %d\n" , status);


    }else {
        printf("Fork Failed\n");
    }

    return 0;
}

/* 

    What is /bin/ls internally?

    It’s an executable binary file, created by compiling the source code of the ls program.

    The source code for ls is part of the GNU Coreutils package on most Linux systems.

    This source code is written in C language.

    The binary (/bin/ls) is the compiled machine code your computer runs directly.
*/
