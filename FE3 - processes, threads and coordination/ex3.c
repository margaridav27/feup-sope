#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int continueExecution = 1;

void sig_handler(int signo) { 
    fprintf(stderr, "Process %d received signal %d.\n", signo, getpid());
    fflush(stderr);

    continueExecution = 0;
} 

int main() {
	struct sigaction new_sigint, new_sigusr1;
	sigset_t smask;	
    
	if (sigemptyset(&smask)==-1) perror ("sigsetfunctions");

    //signal handler configuration for SIGINT
	new_sigint.sa_handler = sig_handler; 
	new_sigint.sa_mask = smask; 
	new_sigint.sa_flags = 0; 
	if(sigaction(SIGUSR1, &new_sigint, NULL) == -1) perror ("sigaction");

    //signal handler configuration for SIGUSR1
	new_sigusr1.sa_handler = sig_handler; 
	new_sigusr1.sa_mask = smask; 
	new_sigusr1.sa_flags = 0; 
	if(sigaction(SIGUSR1, &new_sigusr1, NULL) == -1) perror ("sigaction");

    pid_t pid0, pid1;

    // parent process
    printf("Parent process     -> SID: %d   GPID: %d   PID: %d\n", getsid(0), getpgid(0), getpid());
    fflush(stdout);

    if ((pid0 = fork()) == 0) { // child process
        printf("Child process      -> SID: %d   GPID: %d   PID: %d\n", getsid(0), getpgid(0), getpid());
        fflush(stdout);

        if ((pid1 = fork()) == 0) { // grandchild process
            printf("Grandchild process -> SID: %d   GPID: %d   PID: %d\n", getsid(0), getpgid(0), getpid());
            fflush(stdout);
        }

    } 

    while(continueExecution) { } // waiting

	return 0;
}