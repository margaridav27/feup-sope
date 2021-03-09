#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

char *newenviron[] = {"USER=Linus", NULL};

int main() {
	pid_t id;
    int code;
	setbuf(stdout, NULL);

	printf("Parent: %d. USER=%s\n", getpid(), getenv("USER"));

	id = fork();
	switch (id) {
	case -1:
		perror("fork()");
		exit(1);
	case 0: // child
		printf("Child: %d. USER=%s\n", getpid(), getenv("USER"));

		if (execle("/bin/sleep", "sleep", "5", NULL, newenviron) == -1) {
			perror("execle()");
			exit(2);
		}
			
		printf("You will not see this unless execve() fails! Know why?...\n");
		break;
	default: // parent 
        wait(&code);

		printf("Parent still: %d. USER=%s\n", getpid(), getenv("USER"));
        printf("Child process terminaion code: %d\n", code);
	}

	return 0;
}
