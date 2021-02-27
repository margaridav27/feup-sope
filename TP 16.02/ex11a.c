#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[], char* env[]) {
    int fd1, fd2, cnt;

    char* file1 = argv[1];
    char* file2 = argv[2];

    char* buf[1000];

    fd1 = open(file1, O_RDONLY); //file descriptor of file1
    fd2 = open(file2, O_WRONLY); //file descriptor of file2

    if (fd1 == -1) { //open returns -1 upon failure
        printf("Error whilst opening file1.\n");
    }
    else if (fd2 == -1) {
        printf("Error whilst opening file2.\n");
    }
    else {
        cnt = read(fd1, buf, 1000); //returns the number of elements actually read 
        write(fd2, buf, cnt);
    }

    close(fd1);
    close(fd2);
}