# include <stdio.h>
# include <fcntl.h> // for open() & O_RDONLY
# include <unistd.h> // for read() & close()
# include <string.h> // for strcpy


int main (){

    char buffer[100] = "Lmao, I am writing to a file.";
    int fd = open("example.txt", O_WRONLY);

    //strcpy(buffer, "Lmao, I am writing to a file.");


    if(fd == -1){
        perror("open");
        return 1;
    }

    ssize_t bytesWrite = write(fd, buffer, sizeof(buffer));

    if(bytesWrite== -1){
        perror("write");
        return 2;
    }


    close(fd);
    return 0;

}