#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define NTHREADS 2

void *func(void *a) {
    switch(*((int*) a)) {
        case 0:
            printf("Operating ");
            break;
        case 1:
            printf("Systems\n");
            break;
    }
    
	pthread_exit(NULL);	
}

int main() {
	int i;	
	pthread_t ids[NTHREADS]; 

	for(i = 0; i < NTHREADS; i++) {
        int *val = malloc(sizeof(int));
        *val = i;

		if (pthread_create(ids + i, NULL, func, (void*) val) != 0) {
            perror("Failed to create thread.\n");
			exit(-1); 
        }
	}

	for(i = 0; i < NTHREADS; i++) {
		pthread_join(ids[i], NULL);	
	}

	return 0;	
}
