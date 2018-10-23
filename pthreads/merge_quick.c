#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int n;

void *merge_runner(void * param);
void *quick_runner(void * param);

void merge_sort(int arr[], int l, int r);
void merge(int arr[], int l, int mid, int h);

int partition (int arr[], int low, int high); 
void quick(int arr[], int l, int h);

void swap(int* a, int* b);

void *merge_runner(void * param)
{
    int *arr = (int *)param;
    merge_sort(arr, 0, n-1);
    printf("Merge sort array: \n");
    for(int i=0;i<n;i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    pthread_exit(0);
}

void merge_sort(int arr[], int l, int h)
{
    if(l < h){
        int mid = l + (h-l)/2;

        merge_sort(arr, l, mid);
        merge_sort(arr, mid+1, h);
        merge(arr, l, mid, h);
    }
}

void merge(int arr[], int l, int mid, int h)
{
    int i, j, k;
    int n1 = mid - l + 1;
    int n2 = h - mid;

    int left[n1], right[n2];
    for(int i=0;i<n1;i++){
        left[i] = arr[l+i];
    }

    for(int j=0;j<n2;j++){
        right[j] = arr[mid+1+j];
    }

    i=0,j=0,k=l;

    while(i<n1 && j<n2){
        if(left[i] <= right[j]){
            arr[k] = left[i];
            i++;
        }
        else{
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while(i<n1){
        arr[k] = left[i];
        i++,k++;
    }

    while(j<n2){
        arr[k] = right[j];
        j++,k++;
    }
}

void *quick_runner(void * param)
{
    int *arr = (int *)param;
    quick(arr, 0, n-1);
    printf("Quick sort array: \n");
    for(int i=0;i<n;i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    pthread_exit(0);
}

void quick(int arr[], int low, int high)
{
    if (low < high) 
    {  
        int pi = partition(arr, low, high); 
  
        quick(arr, low, pi - 1); 
        quick(arr, pi + 1, high); 
    } 
}

int partition (int arr[], int low, int high) 
{ 
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high- 1; j++) 
    { 
        if (arr[j] <= pivot) 
        { 
            i++;
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 

void swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 

int main()
{
    printf("Enter the size of the array: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter the array elements: ");
    for(int i=0;i<n;i++){
        scanf("%d", &arr[i]);
    }

    pthread_t tid;
    pthread_attr_t attr;
    
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, merge_runner, (void *) arr);

    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, quick_runner, (void *) arr);

    pthread_join(tid, NULL);
    return 0;
}