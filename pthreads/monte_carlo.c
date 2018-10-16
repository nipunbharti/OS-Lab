#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define INT 10000

double rand_x, rand_y, dist;
int cricle_points=0, square_points=0;

void *runner(void *param)
{
    rand_x = (double)(rand() % (INT+1))/INT;
    rand_y = (double)(rand() % (INT+1))/INT;
    dist = (rand_x*rand_x) + (rand_y*rand_y);    
    if(dist <= 1){
        cricle_points++;
    }
    square_points++;
    pthread_exit(0);
}

int main()
{
    srand(time(NULL));
    clock_t t;
    pthread_t tid;
    pthread_attr_t attr;
    int j=0;
    t = clock();
    for(int i=0;i<INT;i++){
        pthread_attr_init(&attr);
        pthread_create(&tid, &attr, runner, NULL);   
    // rand_x = (double)(rand() % (INT+1))/INT;
    // rand_y = (double)(rand() % (INT+1))/INT;
    // dist = (rand_x*rand_x) + (rand_y*rand_y);    
    // if(dist <= 1){
    //     cricle_points++;
    // }
    // square_points++;
    }

    pthread_join(tid, NULL);

    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    double pi = (double)(4*cricle_points)/square_points;
    printf("Estimated value: %f\n", pi);
    printf("Took %f seconds to execute \n", time_taken); 
    return 0;
}