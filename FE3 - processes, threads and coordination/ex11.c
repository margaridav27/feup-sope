#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUF_SIZE 20
#define MAX_ITER 100000
long count;
long iter;

pthread_mutex_t mutex_consumer;
pthread_mutex_t mutex_producer;

void *produce(void *arg) {
	while (iter < MAX_ITER) {
		pthread_mutex_lock(&mutex_producer);

		if (count < BUF_SIZE) {
			printf("\n%ld", count);
			count++;
		}

		pthread_mutex_unlock(&mutex_producer);
	}

	printf("\nEND of thread %lu!\n", (unsigned long)pthread_self());
	
	return (NULL);
}

void *consume(void *arg) {
	while (iter < MAX_ITER) {
		pthread_mutex_lock(&mutex_consumer);

		if (count < BUF_SIZE) {
			printf("\n%ld", count);
			count--;
		}

		pthread_mutex_unlock(&mutex_consumer);
	}

	printf("\nEND of thread %lu!\n", (unsigned long)pthread_self());
	
	return (NULL);
}

int main(int argc, char *argv[]) {
    pthread_mutex_init(&mutex_producer, NULL);
	pthread_mutex_init(&mutex_consumer, NULL);

	pthread_t *ptid;
	int nthreads;
	int i;

	int thtype = 0; // producer - 0 / consumer - 1

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

		if (thtype == 0) { // create producer thread
			if (pthread_create(&ptid[i], NULL, produce, NULL) != 0) {
				perror("pthread_create");
				exit(3);
			}
		} else { // create consumer thread
			if (pthread_create(&ptid[i], NULL, consume, NULL) != 0) {
				perror("pthread_create");
				exit(3);
			}
		}

		thtype = (thtype + 1) % 2; // alternating between types
	}

	for (i = 0; i < nthreads; i++) pthread_join(ptid[i], NULL);

	printf("\nEND!\n");

	pthread_mutex_destroy(&mutex_producer);
	pthread_mutex_destroy(&mutex_consumer);
	return 0;
}


