#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[], char* env[]) {
    printf("I am the parent.\n");

    int id = fork();

    switch(id) {
        case -1: perror ("fork"); exit(1);
        case 0: printf("I am the child.\n"); break;
        default: printf("I am the parent of %d.\n", id);
    }

    printf("I am the parent or the child.\n");
}

/*
output:
I am the parent. 
I am the parent of 9491.
I am the parent or the child.
I am the child.
I am the parent or the child.

** on the parent process **
I am the parent. 

** fork call was made, two processes are now running at the same time 
- the parent (the original process) and child created **

** fork returns a value that depends on the process that is being considered
- the parent process receives a return value that corresponds to the PID of the process child created
- the child process receives a return value of 0, upon success **

** while on the child process **
I am the parent of 9491.
I am the parent or the child.

** while on the parent process **
I am the child.
I am the parent or the child.

** notice that "I am the parent or the child." is printed twice since both processes are running at the same time **

*/