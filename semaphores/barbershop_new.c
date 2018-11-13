#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

int N, M;
int customers=0;
sem_t mutex, customer, barber;

void *customer_runner(void *arg)
{
        int i = (int) arg;
        sem_wait(&mutex);
        if(customers == N+1) {
                printf("Customer %d walks out\n", i);
                sem_post(&mutex);
                pthread_exit(0);
        }

        printf("Customer %d enters the shop\n", i);
        customers++;
        sem_post(&mutex);

        printf("Customer %d waits\n", i);
        sem_post(&customer);
        sem_wait(&barber);
        int no_of_cust;
        sem_getvalue(&customer, &no_of_cust);
        printf("Barber is cutting hair and %d customers are there and %d is getting haircut\n", no_of_cust, i);
        sleep(1);

        sem_wait(&mutex);
        customers--;
        sem_post(&mutex);
}

void *barber_runner(void *arg)
{
        while(1) {
                sem_wait(&customer);
                sem_post(&barber);
                sleep(1);
        }
}

int main()
{
        printf("Enter the number of chairs: ");
        scanf("%d", &N);
        printf("Enter the number of customers: ");
        scanf("%d", &M);
        sem_init(&mutex, 0, 1);
        sem_init(&customer, 0, 0);
        sem_init(&barber, 0, 0);

        pthread_t customer_tid[M], barber_tid;

        pthread_create(&barber_tid, NULL, barber_runner, (void *) NULL);
        for(int i=0;i<M;i++) {
                pthread_create(&customer_tid[i], NULL, customer_runner, (void *) i+1);
        }

        for(int i=0;i<N;i++) {
                pthread_join(customer_tid[i], NULL);
        }
        return 0;
}