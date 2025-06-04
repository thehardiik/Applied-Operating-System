
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>



void pipeline(char* process1, char* process2){

    int fd[2];


    if(pipe(fd) == -1){
        perror("Pipe");
        return;
    }

    pid_t pid = fork();

    if(pid < 0){
        perror("Fork");
        return;
    }

    if(pid > 0){
        // Parent Process

        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);

        execlp("cat", "cat", "main.txt", (char*) NULL);
        perror("Exec");

    }else{

        // Child Process
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);

        execlp("grep", "grep", "hello", (char*) NULL);
        perror("Exec");
    }

}


int main(){
    pipeline("cat" , "grep");
    return 0;
}