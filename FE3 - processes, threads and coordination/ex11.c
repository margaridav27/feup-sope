#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUF_SIZE 20
#define MAX_ITER 10000

volatile long count = 0; // buffer index simulator
volatile long iter = 0; // iteration counter

sem_t empty; // how many slots are free
sem_t full; // how many slots have content
pthread_mutex_t mutex; // make buffer addition/removal atomic

void *producer(void *arg) {
	while (1) {
		sem_wait(&empty); // decrease the number of empty slots
		pthread_mutex_lock(&mutex);

		if (iter < MAX_ITER) {
			iter++;
			count++;

			printf("Producer %ld. Count = %ld. Iteration no. %ld\n", pthread_self(), count, iter);

			pthread_mutex_unlock(&mutex); 
			sem_post(&full); // increase the number of slots with content
		} 
		else { // no iterations left, stop the execution
			pthread_mutex_unlock(&mutex);
			sem_post(&full);
			break;
		}
	}

	return NULL;
}

void *consumer(void *arg) {
	while (1) {
		sem_wait(&full); // decrease the number of slots with content
		pthread_mutex_lock(&mutex);

		if (iter < MAX_ITER) {
			iter++;
			count--;

			printf("Consumer %ld. Count = %ld. Iteration no. %ld\n", pthread_self(), count, iter);

			pthread_mutex_unlock(&mutex);
			sem_post(&empty); // increase the number of empty slots
		} 
		else { // no iterations left, stop the execution
			pthread_mutex_unlock(&mutex);
			sem_post(&empty); 
			break;
		}
	}

	return NULL;
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