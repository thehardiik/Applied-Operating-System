# include <stdio.h>
# include <fcntl.h> // for open() & O_RDONLY
# include <unistd.h> // for read() & close()


int main (){

    char buffer[100];
    int fd = open("example.txt", O_RDONLY);

    if(fd == -1){
        perror("open");
        return 1;
    }


    // To shift the pointer 
    off_t newPos = lseek(fd, 10, SEEK_SET);

    if(newPos == -1){
        perror("Pointer");
        return 3;
    }

    ssize_t bytesRead = read(fd, buffer, sizeof(buffer)-1);

    if(bytesRead == -1){
        perror("read");
        return 2;
    }

    buffer[bytesRead] = "\0";
    printf("Data Read: %s" , buffer);

    close(fd);
    return 0;

}