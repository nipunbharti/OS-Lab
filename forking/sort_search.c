#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int compare(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}

int binary_search(int a[], int n, int start, int end);

int main()
{
	int a[100];
	printf("Enter the array:\n");
	for(int i=0;i<6;i++){
		scanf("%d", &a[i]);
	}
	pid_t pid = vfork();
	if(pid == 0){
		qsort(a, 6, sizeof(a[0]), compare);
		_exit(0);
	}
	else if(pid > 0){
		wait(NULL);
		int n;
		printf("Enter the number to search:\n");
		scanf("%d", &n);
		int searched = binary_search(a, n, 0, 5);
		(searched == -1) ? printf("Not found.\n") : printf("Element found at %d\n", searched);
	}
	return 0;
}

int binary_search(int a[], int n, int start, int end)
{
	if(end >= start){
		int mid = start + (end-1)/2;
		if(a[mid] == n){
			return mid;
		}
		else if(a[mid] < n){
			return binary_search(a, n, mid+1, end);
		}
		else{
			return binary_search(a, n, start, mid-1);
		}
	}
	return -1;
}