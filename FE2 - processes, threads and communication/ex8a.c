#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

/* see the comments on ssignal.c to a better understanding of what is going on */

void func(int signo) { } //does not need to do anything

int main() {
	struct sigaction new, old;
	sigset_t smask;	

	if (sigemptyset(&smask)==-1) 
		perror ("sigsetfunctions");

	new.sa_handler = func; 
	new.sa_mask = smask; 
	new.sa_flags = 0; 

	if(sigaction(SIGUSR1, &new, &old) == -1)
		perror ("sigaction");

    int pid = fork();

    switch(pid) {
        case -1: 
            perror ("Fork failed.\n"); 
            exit(1);
        case 0: // child process
            printf("Hello "); 
            kill(pid, 10); //signal 10 <=> SIGUSR1
            break;
        default: // parent process
            pause();
            printf("World!\n");
    } 

	return 0;
}
