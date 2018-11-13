#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 20
#define THREAD_MAX 4
int arr[MAX];
int part = 0;

void merge(int low, int mid, int high)
{
    int i,j,k;
    int n1 = mid-low+1;
    int n2 = high-mid;

    int left[n1], right[n2];
    for(i=0;i<n1;i++){
        left[i] = arr[i+low];
    }

    for(j=0;j<n2;j++){
        right[j] = arr[j+mid+1];
    }

    i=0,j=0,k=0;
    while(i<n1 && j<n2){
        if(left[i] <= right[j]){
            arr[k] = left[i];
            i++;
        }
        if(left[i] > right[j]){
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while(i<n1){
        arr[k] = left[i];
        i++, k++;
    }

    while(j<n2){
        arr[k] = right[j];
        j++, k++;
    }
}

void merge_sort(int low, int high)
{
    int mid = low + (high-low)/2;
    if(low < high){
        merge_sort(low, mid);
        merge_sort(mid+1, high);
        merge(low, mid, high);
    }
}

void *merge_parallel(void *param)
{
    int thread_part = part++;
    int low = (thread_part)*(MAX/4);
    int high = (thread_part*1)*(MAX/4) - 1;

    int mid = low + (high-low)/2;
    if(low < high){
        merge_sort(low, mid);
        merge_sort(mid+1, high);
        merge(low, mid, high);
    }
    pthread_exit(0);
}

int main()
{
    for(int i=0;i<MAX;i++){
        arr[i] = rand() % 100;
    }

    pthread_t tid[THREAD_MAX];
    for(int i=0;i<THREAD_MAX;i++){
        pthread_create(&tid[i], NULL, merge_parallel, NULL);
    }

    for(int i=0;i<THREAD_MAX;i++){
        pthread_join(tid[i], NULL);
    }
}