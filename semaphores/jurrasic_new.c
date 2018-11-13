#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

int no_of_cars;
int no_of_passenger;
sem_t mutex, car, passenger;

void *passenger_runner(void *i)
{
        int arg = (int) i;
        printf("Passenger %d enters.\n", arg);
        sem_wait(&car);
        printf("Passenger %d is taking a ride.\n", arg);
        sleep(1);
        pthread_exit(0);
}

void *car_runner(void *i)
{       
        while(no_of_passenger >= 0) {
                int arg = (int) i;
                sem_wait(&passenger);
                printf("%d car is busy\n", arg);
                sleep(1);
                sem_post(&car);
                sem_wait(&mutex);
                no_of_passenger--;
                sem_post(&mutex);
        }
        pthread_exit(0);
}

int main()
{
        int N, M;
        printf("Enter the no of passengers: \n");
        scanf("%d", &N);
        printf("Enter the no of cars: \n");
        scanf("%d", &M);
        no_of_cars = M;
        no_of_passenger = N;
        sem_init(&mutex, 0, 1);
        sem_init(&passenger, 0, N);
        sem_init(&car, 0, M);

        pthread_t passenger_tid[N], car_tid[M];
        for(int i=0;i<N;i++){
                pthread_create(&passenger_tid[i], NULL, passenger_runner,(void *) i);
        }

        for(int i=0;i<M;i++){
                pthread_create(&car_tid[i], NULL, car_runner, (void *) i);
        }

        for(int i=0;i<N;i++){
                pthread_join(passenger_tid[i], NULL);
        }

        for(int i=0;i<M;i++){
                pthread_join(car_tid[i], NULL);
        }
}