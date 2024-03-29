/*
*	Example of threads in action
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define NTHREADS 3

void *rot(void *a) {
	printf("\n\t In thread PID: %d ; TID: %lu.", getpid(), (unsigned long) pthread_self());

	/*
	pthread_exit function terminates the calling thread and returns a value, in this case NULL
	this value becomes available in the so called main thread which calls pthread_join
	*/
	pthread_exit(NULL);	
}

int main() {
	int i;	// thread counter
	pthread_t ids[NTHREADS]; // storage of (system) thread identifiers - TID

	setbuf(stdout, NULL);	// only for debugging
	printf("\nMain thread PID: %d ; TID: %lu.\n", getpid(), (unsigned long) pthread_self());

	// new threads creation
	for(i = 0; i < NTHREADS; i++) {
		if (pthread_create(&ids[i], NULL, rot, NULL) != 0) {
			exit(-1); // here, we decided to end process
		}
		else {
			printf("\nNew thread %d ; TID: %lu.", i, (unsigned long) ids[i]);
		}
	}

	// wait for finishing of created threads
	for(i = 0; i < NTHREADS; i++) {
		pthread_join(ids[i], NULL);	// note: threads give no termination code
		printf("\nTermination of thread %d: %lu.", i, (unsigned long)ids[i]);
	}

	printf("\n");
	pthread_exit(NULL);	// not really necessary because at this point there is just the main thread 
	return 0;	// will not run this because we exited the thread with the previous line of code
}
