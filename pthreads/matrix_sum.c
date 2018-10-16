#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int n;
int mat1[10][10];
int mat2[10][10];
int sum_mat[10][10];

void *sum(void *param)
{
    int row = (int)param;
    for(int i=0;i<n;i++){
        sum_mat[row][i] = mat1[row][i] + mat2[row][i];
    }
    pthread_exit(0);
}

int main()
{
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d", &mat1[i][j]);   
        }    
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d", &mat2[i][j]);   
        }    
    }

    pthread_t tid[n];
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    for(int i=0;i<n;i++){
        pthread_create(&tid[i], &attr, &sum,(void *) i);
    }

    for(int i=0;i<n;i++){
        pthread_join(tid[i], NULL);
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%d ", sum_mat[i][j]);  
        }    
    }
    printf("\n");
    return 0;
}