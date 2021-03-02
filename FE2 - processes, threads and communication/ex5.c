#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[], char* env[]) {
    int id = fork();
    int value; 

    switch(id) {
        case -1: 
            perror ("fork"); 
            exit(1);
        case 0: 
            printf("Hello "); 
            break;
        default: 
            wait(&value);
            printf("World!\n");
    }
}

