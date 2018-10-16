#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void *prime_generate(void *param);

int main(int argc, char *argv[])
{
    pthread_t tid; // Descriptor
    pthread_attr_t attr; // Thread attributes
    pthread_attr_init(&attr); // Thread attr initialization
    pthread_create(&tid, &attr, prime_generate,(void *) argv[1]); // Creating a thread
    pthread_join(tid, NULL); // Ending the thread
    return 0;
}

void *prime_generate(void *param)
{
    int limit = atoi(param);
    int num[limit+1];
    for(int i=0;i<=limit;i++){
        num[i] = 1;
    }

    for(int p=2;p*p<=limit;p++){
        if(num[p]){
            for(int i=p*2;i<=limit;i+=p){
                num[i] = 0;
            }
        }
    }
    
    for(int i=2;i<=limit;i++){
        if(num[i]){
            printf("%d ", i);
        }
    }
    
    printf("\n");
    pthread_exit(0);
}