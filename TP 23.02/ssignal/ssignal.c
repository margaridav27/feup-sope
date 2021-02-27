/*
*	Example of signals in action (with SIGACTION)
*/
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void func(int signo) {
	fprintf(stderr, "\nReceived signal %d!\n", signo);
	}

int main() {
	struct sigaction new, old;
	sigset_t smask;	// defines signals to block while func() is running


	/*
	sigemptyset initializes the signal set (sigset_t) 'smask' to empty
	with all the signals excluded from the set
	the function returns 0 on success and -1 on error
	*/

	// prepare struct sigaction

	if (sigemptyset(&smask)==-1) // block no signal
		perror ("sigsetfunctions");

	new.sa_handler = func; /* pointer to a signal handling function 
						      which receives the signal number (signo)
						      as its only argument */

	new.sa_mask = smask; /* specifies a mask of signals which should be blocked
							during the execution of the signal handler 
							in this case, no signals should be blocked */

	new.sa_flags = 0; // usually works

	/*
	the sigaction system call is used to change the action taken by a process
	on receipt of a specific signal
	
	int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);

	*/
	if(sigaction(SIGUSR1, &new, &old) == -1)
		perror ("sigaction");

	printf("\nSIGUSR1 handler is ready...");
	printf("\n\t Try: \"sh> kill -SIGUSR1 %d\".\n", getpid());

	/*
	pause causes the calling process (or thread) to sleep until a signal is delivered that
    either terminates the process or causes the invocation of a signal-catching function
	*/
	pause(); // wait

	return 0;
}
