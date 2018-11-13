#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5
int buffer=0;
char enter=0;
sem_t mutex, items;

void *producer_runner(void *arg)
{
	while(1) {
		while(enter != '\r' && enter != '\n') {
			enter = getchar();
		}
		printf("Got an event!\n");
		sem_wait(&mutex);
		buffer++;
		printf("Buffer incremented to: %d\n", buffer);
		sem_post(&mutex);
		sem_post(&items);
	}
	pthread_exit(0);
}

void *customer_runner(void *arg)
{
	sem_wait(&items);
	sem_wait(&mutex);
	buffer--;
	printf("Buffer decremented to: %d\n", buffer);
	sem_post(&mutex);
	enter=0;
	printf("Doing the event event\n");
	sleep(1);
	pthread_exit(0);
}

int main()
{
	sem_init(&mutex, 0, 1);
	sem_init(&items, 0, 0);

	pthread_t producer_tid, customer_tid[N];

	pthread_create(&producer_tid, NULL, producer_runner, (void *) NULL);
	for(int i=0;i<N;i++) {
		pthread_create(&customer_tid[i], NULL, customer_runner, (void *) i);
	}

	pthread_join(producer_tid, NULL);
	for(int i=0;i<N;i++) {
		pthread_join(customer_tid[i], NULL);
	}
	return 0;
}