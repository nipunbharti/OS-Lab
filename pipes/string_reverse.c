#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <ctype.h>

#define BS 1024 
#define REND 0 
#define WEND 1

int main()
{
	char wm1[BS];
    char wm2[BS];
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

        fgets(wm1, BS, stdin);
        write(fd1[WEND], wm1, strlen(wm1));
        read(fd2[REND], rm2, BS);
        printf("%s\n", rm2);
	}
	else if(pid == 0){
		close(fd1[WEND]);
        close(fd2[REND]);

        read(fd1[REND], rm1, BS);
        for(int i=0;i<strlen(rm1);i++){
            if(islower(rm1[i])){
                rm1[i] = toupper(rm1[i]);
            }
            else if(isupper(rm1[i])){
                rm1[i] = tolower(rm1[i]);
            }
        }
        write(fd2[WEND], rm1, strlen(rm1));
	}
	return 0;
}