#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex, rw_mutex;
int data=0, rcount=0;

void *reader(void *arg)
{
    int tid = (int) arg;
    sem_wait(&mutex);
    rcount++;
    if(rcount == 1){
        sem_wait(&rw_mutex);
    }
    sem_post(&mutex);

    printf("Data read by reader %d is %d\n", tid, data);
    sleep(1);

    sem_wait(&mutex);
    rcount--;
    if(rcount == 0){
        sem_post(&rw_mutex);
    }
    sem_post(&mutex);
    pthread_exit(0);
}

void *writer(void *arg)
{
    int tid = (int) arg;
    sem_wait(&rw_mutex);
    data++;
    printf("Data written by writer %d is %d\n", tid, data);
    sleep(1);
    sem_post(&rw_mutex);
    pthread_exit(0);
}

int main()
{
    pthread_t rtid[5], wtid[5];
    sem_init(&mutex, 0, 1);
    sem_init(&rw_mutex, 0, 1);

    for(int i=0;i<5;i++){
        pthread_create(&wtid[i], NULL, writer, (void *) i);
        pthread_create(&rtid[i], NULL, reader, (void *) i);
    }

    for(int i=0;i<5;i++){
        pthread_join(wtid[i], NULL);
        pthread_join(rtid[i], NULL);
    }
}