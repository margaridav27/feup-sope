#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define NTHREADS 5

void *rot(void *a) {
    printf("\n\t In thread no. %d. The main thread will read the value %d.\n", *((int*) a), *((int*) a) * *((int*) a));
    *((int*) a) *= *((int*) a);
    sleep(5);
	pthread_exit(a);	
}

int main() {
	int i;	
	pthread_t ids[NTHREADS]; 
	
	for(i = 0; i < NTHREADS; i++) {
        int *val = malloc(sizeof(int));
        *val = i;

		if (pthread_create(ids + i, NULL, rot, (void*) val) != 0) {
			exit(-1); 
        }
		else {
			printf("\nThread %d has been created.\n", i);
		}
	}

	for(i = 0; i < NTHREADS; i++) {
        int **retval = (int**) malloc(sizeof(int*));
		pthread_join(ids[i], (void**) retval);	
		printf("\nTermination of thread %d. The thread returned %d.\n", i, **retval);
	}

	printf("\n");
	pthread_exit(NULL);
	return 0;	
}
