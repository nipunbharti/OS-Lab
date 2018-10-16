#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	char command[100];
	FILE *fp;
	while(1){
		pid_t pid = vfork();
		if(pid == 0){
			printf("$:");
			fgets(command, 100, stdin);
			_exit(0);
		}
		else if(pid > 0){
			int count=0;
			if(command[0] == 33){
				fp = fopen("log.txt","r");
				if(command[1] == 33){
					while(!feof(fp)){
						char c = fgetc(fp);
						printf("%c", c);
					}
				}
				else{
					fseek(fp, 0, SEEK_SET);
					while(!feof(fp)){
						if(fgetc(fp) == '\n'){
							count++;
						}
					}
					int new_count=0;
					fseek(fp, 0, SEEK_SET);
					int x = command[1]-'0';
					while(new_count != count-x){
						if(fgetc(fp) == '\n'){
							new_count++;
						}
					}
					while(!feof(fp)){
						printf("%c", fgetc(fp));
					}
				}
				fclose(fp);
			}
			else{
				system(command);
			}
			fp = fopen("log.txt","a+");
			fprintf(fp, "%s", command);
			fclose(fp);
			wait(NULL);
		}
	}
	return 0;
}