#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUF_SIZE 20
#define MAX_ITER 10000
long count;
long iter;

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

void *producer(void *arg) {
	if (iter >= MAX_ITER || count == BUF_SIZE) return (NULL);

	sem_wait(&empty);
	pthread_mutex_lock(&mutex);

	iter++;
	count++;

	printf("\n%ld\t%ld", count, iter);

	pthread_mutex_unlock(&mutex);
	sem_post(&full);

	return (NULL);
}

void *consumer(void *arg) {
	if (iter >= MAX_ITER || count == BUF_SIZE) return (NULL);

	sem_wait(&full);
	pthread_mutex_lock(&mutex);

	iter++;
	count--;

	printf("\n%ld\t%ld", count, iter);

	pthread_mutex_unlock(&mutex);
	sem_post(&empty);

	return (NULL);
}

int main(int argc, char *argv[]) {
	pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUF_SIZE);
	sem_init(&full, 0, 0);
	
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
			if (pthread_create(&ptid[i], NULL, producer, NULL) != 0) {
				perror("pthread_create");
				exit(3);
			}
		} else { // consumer thread
			if (pthread_create(&ptid[i], NULL, consumer, NULL) != 0) {
				perror("pthread_create");
				exit(3);
			}
		}
	}

	for (i = 0; i < nthreads; i++) pthread_join(ptid[i], NULL);

	pthread_mutex_destroy(&mutex);
	sem_destroy(&empty);
	sem_destroy(&full);
	return 0;
}