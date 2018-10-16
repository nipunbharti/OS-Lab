#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	char command[100];
	while(1){
		pid_t pid = vfork();
		if(pid == 0){
			printf("$:");
			fgets(command, 100, stdin);
			_exit(0);
		}
		else if(pid > 0){
			system(command);
			wait(NULL);
		}
	}
	return 0;
}