#include <unistd.h>
#include <stdio.h>

int main() {
    int status = rmdir("mydir");
    
    if (status == 0) {
        printf("Directory removed successfully!\n");
    } else {
        perror("rmdir");
    }
    return 0;
}
