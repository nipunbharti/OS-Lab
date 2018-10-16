#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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

	int src_file = open("indirection.txt", O_RDONLY);
	int dest_file = open("copy_sim.txt", O_WRONLY | O_CREAT, 00700);

	if(pid > 0){
		close(fd[REND]);
		while((nb=read(src_file, rm, BS)) > 0){
			write(fd[WEND], rm, strlen(rm));
		}
	}
	else if(pid == 0){
        close(fd[WEND]);
		read(fd[REND], rm, BS);
		write(dest_file, rm, strlen(rm));
	}
	return 0;
}