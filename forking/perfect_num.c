#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int is_perfect(int n)
{
	int sum = 1;
	for(int i=2;i*i<=n;i++){
		if(n%i == 0){
			sum = sum + i + n/i;
		}
	}

	if(sum == n && n!=1){
		return 1;
	}

	return 0;
}

int main()
{
	int lower_limit, upper_limit;
	pid_t pid = vfork();
	if(pid > 0){
		wait(NULL);
		for(int i=lower_limit;i<upper_limit;i++){
			if(is_perfect(i)){
				printf("%d ", i);
			}
		}
	}
	else if(pid == 0){
		printf("Enter the lower limit and the upper limit:\n");
		scanf("%d%d",&lower_limit,&upper_limit);
		_exit(0);
	}
	return 0;
}