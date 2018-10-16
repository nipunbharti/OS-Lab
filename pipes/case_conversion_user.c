#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <ctype.h>

#define BS 2048
#define REND 0 
#define WEND 1

int main()
{
    char rm[BS];
	int fd[2], nb;
	if(pipe(fd) == -1){
		perror("Error while creation");
		return -1;
	}

	pid_t pid = fork();

	if(pid > 0){
		while((nb=read(fd[REND], rm, BS)) > 0){
            for(int i=0;i<nb;i++){
                rm[i] = toupper(rm[i]);
            }
            write(1, rm, nb);
        }
		exit(0);
	}
	else if(pid == 0){
		dup2(fd[WEND], 1);
        execlp("ls", "ls", NULL);
	}
	return 0;
}