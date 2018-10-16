#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int size;

int comparator(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

void *median(void *param);
void *mean(void *param);
void *mode(void *param);

void *mean(void *param)
{
    int sum = 0;
    int *arr = (int *)param;
    for(int i=0;i<size;i++){
        sum += arr[i];
    }
    printf("Mean: %d\n", sum/size);
    pthread_exit(0);
}

void *median(void *param)
{
    int *arr = (int *)param;
    printf("Median: %d\n", arr[size/2]);
    pthread_exit(0);
}

void *mode(void *param)
{  
    int *arr = (int *) param;
	int max_count = 1,res = arr[0],curr_count = 1;
	for(int i=1;i<size;i++)
	{
		if(arr[i] == arr[i-1])
			curr_count++;
		else
		{
			if(curr_count > max_count)
			{
				max_count = curr_count;
				res = arr[i-1];
			}
			curr_count = 1;
		}
	}
	if(curr_count > max_count)
	{
		max_count = curr_count;
		res = arr[size - 1];
	}
	printf("Mode: %d\n", res);
    pthread_exit(0);
}


int main()
{
    printf("Enter the number of elements in the array: ");
    scanf("%d", &size);
    int arr[size];
    printf("Enter the elements: ");
    for(int i=0;i<size;i++){
        scanf("%d", &arr[i]);
    }

    qsort(arr, size, sizeof(int), comparator);

    pthread_t tid;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, mean, (void *) arr);
    printf("First:%d\n",tid);
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, median, (void *) arr);
    printf("Second:%d\n",tid);
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, mode, (void *) arr);
    printf("Third:%d\n",tid);
    pthread_join(tid, NULL);
    printf("last:%d\n",tid);

    return 0;
}