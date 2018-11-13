#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex;

void *s1(void *arg)
{
	printf("Statement 1\n");
	sem_post(&mutex);
}

void *s2(void *arg)
{
	sem_wait(&mutex);
	printf("Statement 2\n");
}

int main()
{
	sem_init(&mutex, 0, 0);
	pthread_t tid;

	pthread_create(&tid, NULL, s1, (void *) NULL);
	pthread_create(&tid, NULL, s2, (void *) NULL);

	pthread_join(tid, NULL);

	return 0;
}