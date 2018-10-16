#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

int den=0;

void sigint(){
    printf("Sigint\n");
    signal(SIGINT, sigint);
}

void sigquit(){
    printf("Sigquit\n");
    den=1;
    signal(SIGFPE, SIG_DFL);
}

int main()
{
    signal(SIGFPE, sigquit);
    int a=9/den;
    return 0;
}