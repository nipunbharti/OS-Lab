#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define BS 1024 
#define REND 0 
#define WEND 1

int main()
{
	char wm[BS] = "Unidirectional pipe";
	char rm[BS];
	int fd[2];
	
	if(pipe(fd) == -1){
		perror("Pipe");
		return -1;
	}

	pid_t pid = fork();
	if(pid > 0){
		close(fd[REND]);
		write(fd[WEND], wm, strlen(wm));
		close(fd[WEND]);
	}
	else if(pid == 0){
		close(fd[WEND]);
		read(fd[REND], rm, BS);
		printf("%s\n", rm);
		close(fd[REND]);
	}
	return 0;
}