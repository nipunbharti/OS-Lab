#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>

#define BS 1024 
#define REND 0 
#define WEND 1

void fibonacci(int n);

int main()
{
	char wm[BS], rm[BS];
	int fd[2];
	if(pipe(fd) == -1){
		perror("Error while creation");
		return -1;
	}

	pid_t pid = fork();
    
    int file = open("indirection.txt", O_WRONLY | O_APPEND | O_CREAT, 00700);

	if(pid > 0){
        close(fd[WEND]);
        read(fd[REND], rm, BS);
        dup2(file, 1);
		fibonacci(atoi(rm));
		close(fd[REND]);
	}
	else if(pid == 0){
		close(fd[REND]);
		scanf("%s", wm);
        write(fd[WEND], wm, strlen(wm));
		close(fd[WEND]);
	}
	return 0;
}

void fibonacci(int n)
{
    int a=0, b=1, sum;
    printf("%d\n%d\n", a, b);
    sum = a+b;
    for(int i=2;i<n;i++){
        int x = sum;
        printf("%d\n", sum);
        sum = sum + b;
        a = b;
        b = x;
    }
}