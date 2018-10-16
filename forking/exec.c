#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	int ch;
	char *cmd[] = {"ls","-al",NULL};
	printf("1. execl\n2. execp\n3. execv\n");
	scanf("%d", &ch);
	switch(ch){
		case 1:
			execl("/bin/ls","ls","-al",NULL);
			break;
		case 2:
			execlp("ls","ls","-al",NULL);
			break;
		case 3:
			execvp(cmd[0], cmd);
			break;
		default:
			printf("Wrong choice\n");
	}
	return 0;
}