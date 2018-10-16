#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	int n;
	pid_t pid = vfork();
	while(n!=1){
		if(pid == 0){
			printf("Enter the value of n:\n");
			scanf("%d", &n);
			_exit(0);
		}
		else if(pid > 0){
			wait(NULL);
			if(n%2 == 0){
				n=n/2;
			}
			else{
				n=(3*n)+1;
			}
			printf("%d\n", n);
		}
	}
	return 0;
}