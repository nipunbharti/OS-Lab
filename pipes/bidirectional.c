#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#define BS 1024 
#define REND 0 
#define WEND 1

int main()
{
	char wm1[BS] = "Bi-directional pipe 1";
    char wm2[BS] = "Bi-directional pipe 2";
	char rm1[BS], rm2[BS];
	int fd1[2], fd2[2];
	if(pipe(fd1) == -1){
		perror("Error while creation of first pipe");
		return -1;
	}

    if(pipe(fd2) == -1){
		perror("Error while creation of second pipe");
		return -1;
	}

	pid_t pid = fork();

	if(pid > 0){
		close(fd1[REND]);
        close(fd2[WEND]);
        write(fd1[WEND], wm1, strlen(wm1)); //Step 1
        read(fd2[REND], rm1, BS); // Step 4
        printf("%s\n", rm1);
	}
	else if(pid == 0){
		close(fd1[WEND]);
        close(fd2[REND]);
        read(fd1[REND], rm2, BS); // Step 2
        printf("%s\n", rm2);
        write(fd2[WEND], wm2, strlen(wm2)); // Step 3
	}
	return 0;
}