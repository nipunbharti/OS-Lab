#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int main()
{
    int scope, policy;
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    if(pthread_attr_getscope(&attr, &scope) != 0){
        perror("Error");
    }
    else if(scope == PTHREAD_SCOPE_PROCESS){
        printf("Process scope");
    }
    else if(scope == PTHREAD_SCOPE_SYSTEM){
        printf("System scope");
    }
    else{
        perror("Ouch");
    }

    if(pthread_attr_getschedpolicy(&attr, &policy) != 0){
        perror("Error");
    }
    else if(policy == SCHED_FIFO){
        printf("FIFO");
    }
    else if(policy == SCHED_RR){
        printf("RR");
    }
    else if(policy == SCHED_OTHER){
        printf("OTHER");
    }
    else{
        perror("Ouch");
    }
    return 0;
}