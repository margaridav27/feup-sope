#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUF_SIZE 20
#define MAX_ITER 100000
long count;
long iter;

sem_t semaphore;

void *produce(void *arg) {
	while (count == BUF_SIZE) ;

	sem_wait(&semaphore);

	iter++;
	count++;
	printf("\n%ld\t%ld", count, iter);

	sem_post(&semaphore); 

	return (NULL);
}

void *consume(void *arg) {
	while (count == 0) ;

	sem_wait(&semaphore);

	iter++;
	count--;
	printf("\n%ld\t%ld", count, iter);

	sem_post(&semaphore); 

	return (NULL);
}

int main(int argc, char *argv[]) {
    sem_init(&semaphore, 0, 1);

	pthread_t *ptid;
	int nthreads;
	int i;

	setbuf(stdout, NULL);
	if (argc < 2) {
		printf("\nUsage: %s #threads\n", argv[0]);
		exit(1);
	}
	
	nthreads = atoi(argv[1]);
	ptid = (pthread_t *)malloc(nthreads * sizeof(pthread_t));
	if (ptid == NULL) {
		perror("malloc");
		exit(2);
	}

	for (i = 0; i < nthreads; i++) {

		if (i % 2 == 0) { // producer thread
			if (pthread_create(&ptid[i], NULL, produce, NULL) != 0) {
				perror("pthread_create");
				exit(3);
			}
		} else { // consumer thread
			if (pthread_create(&ptid[i], NULL, consume, NULL) != 0) {
				perror("pthread_create");
				exit(3);
			}
		}
	}

	for (i = 0; i < nthreads; i++) pthread_join(ptid[i], NULL);

	sem_destroy(&semaphore);
	return 0;
}


