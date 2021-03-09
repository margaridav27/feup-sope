/*
*	EXEC: 1st example of typical usage!
*
* Note:	execve is the syscal!
*	execv, execvp, execvpe, execl, execlp, execle are library functions.
*
* Exercise:
* 	change this code to show that USER was changed after the exec.
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

char *cmdline[] = {"sleep", "10", (void *)0};
char *newenviron[] = {"USER=Linus", NULL};

int main() {
	pid_t id;
	setbuf(stdout, NULL); // to make sure printf() have no buffer and so no delay!

	printf("Parent: %d. USER=%s\n", getpid(), getenv("USER"));

	id = fork();
	switch (id) {
	case -1:
		perror("fork()");
		exit(1);
	case 0: // child
		printf("Child: %d. USER=%s\n", getpid(), getenv("USER"));

		printf("Child: check that following exec was succeful with: \"ps x | grep sleep\"\n");

		if (execve("/bin/sleep", cmdline, newenviron) == -1) {
			perror("execve()");
			exit(2);
		}
			
		printf("You will not see this unless execve() fails! Know why?...\n");
		break; // just in case if execve fails
	default: // parent 
		wait(NULL);

		printf("Parent still: %d. USER=%s\n", getpid(), getenv("USER"));
	}

	return 0;
}
