#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>

int main() {
    int status = mkdir("mydir", 0755);
    if (status == 0) {
        printf("Directory created successfully!\n");
    } else {
        perror("mkdir");
    }
    return 0;
}
