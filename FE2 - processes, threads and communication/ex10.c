#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define NTHREADS 2

struct Argument_t {
    int id;
    char* seq1;
    char* seq2;
};

void *executer(void *a) {
    if (((struct Argument_t*) a)->id == 0) {
        printf("%s", ((struct Argument_t*) a)->seq1);
        ((struct Argument_t*) a)->id = 1;
    }
    else if (((struct Argument_t*) a)->id == 1) {
        printf("%s", ((struct Argument_t*) a)->seq2);
    }
    
	pthread_exit(NULL);	
}

int main() {
	int i;	
	pthread_t ids[NTHREADS]; 

    struct Argument_t *arg = malloc(sizeof(struct Argument_t));
    arg->id = 0;
    arg->seq1 = "Operating ";
    arg->seq2 = "Systems\n";

	for(i = 0; i < NTHREADS; i++) {
        int *val = malloc(sizeof(int));
        *val = i;

        if (i == 1) {
            sleep(0.2); //otherwise, both threads would most likely print the same thing
        }

		if (pthread_create(ids + i, NULL, executer, (void*) arg) != 0) {
            perror("Failed to create thread.\n");
			exit(-1); 
        }
	}

	for(i = 0; i < NTHREADS; i++) {
		pthread_join(ids[i], NULL);	
	}

	return 0;	
}
