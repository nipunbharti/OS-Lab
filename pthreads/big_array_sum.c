#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 10
int arr[MAX];
#define MAX_THREAD 4
int part=0;
int sum_array[10] = {0};

void *sum(void *param)
{
    int thread_part = part++;
    for(int i=(thread_part)*(MAX/2);i<(thread_part+1)*(MAX/2);i++){
        sum_array[thread_part] += arr[i];
    }
    pthread_exit(0);
}

int main()
{

    for(int i=0;i<MAX;i++){
        scanf("%d", &arr[i]);
    }
    pthread_t tid[MAX_THREAD];
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    for(int i=0;i<MAX_THREAD;i++){
        pthread_create(&tid[i], &attr, sum, NULL);
    }
    for(int i=0;i<MAX_THREAD;i++){
        pthread_join(tid[i], NULL);
    }
    int total_sum=0;
    for(int i=0;i<5;i++){
        total_sum+=sum_array[i];
    }
    printf("%d\n", total_sum);
    return 0;
}