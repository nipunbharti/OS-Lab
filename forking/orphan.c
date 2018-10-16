#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	pid_t pid = fork();
	if(pid == 0){
		sleep(5);
		printf("Child: %d\n", pid);
	}
	else if(pid > 0){
		printf("Parent: %d\n", pid);
		exit(0);
	}
	printf("Blind print: %d\n", pid);
	return 0;
}