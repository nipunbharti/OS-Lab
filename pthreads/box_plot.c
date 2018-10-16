#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int n;
int arr[100];
float min, max, q1, q2, q3;

int comparator(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

void *min_runner(void *param)
{
    min = arr[0];
    pthread_exit(0);
}

void *max_runner(void *param)
{
    max = arr[n-1];
    pthread_exit(0);
}

void *q2_runner(void *param)
{
    if(n%2 != 0){
        q2 = (float)arr[(n/2)];
    }
    else{
        q2 = (float)(arr[(n/2)-1]+arr[n/2])/2;
    }
    pthread_exit(0);
}

void *q1_runner(void *param)
{
    int mid;
    if(n%2 != 0){
        mid = n/2;
    }
    else{
        mid = (((n/2)-1)+(n/2)/2);
    }
    
    if(mid%2 != 0){
        q1 = (float)arr[(mid/2)];
    }
    else{
        q1 = (float)(arr[(mid/2)-1]+arr[mid/2])/2;
    }

    pthread_exit(0);
}

void *q3_runner(void *param)
{
    int size = n-1;
    int mid;
    if(n%2 != 0){
        mid = n/2;
    }
    else{
        mid = (((n/2)-1)+n/2)/2;
    }
    
    if(((size-mid)+1)%2 != 0){
        q3 = (float)arr[(mid+size)/2];
    }

    else{
        q3 = (float)(arr[(mid+size)/2] + arr[((mid+size)/2)+1])/2;
    }

    pthread_exit(0);
}

int main()
{
    printf("Enter the number of elements:");
    scanf("%d", &n);
    printf("Enter the array:");
    for(int i=0;i<n;i++){
        scanf("%d", &arr[i]);
    }
    qsort(arr, n, sizeof(int), comparator);

    pthread_t tid;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, min_runner,NULL);

    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, max_runner,NULL);

    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, q2_runner,NULL);

    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, q1_runner,NULL);

    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, q3_runner,NULL);

    pthread_join(tid, NULL);
    printf("Min: %f Max: %f Q1: %f Q2: %f Q3: %f", min, max, q1, q2, q3);
    return 0;
}