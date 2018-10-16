#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 3
int mat[N][N];
float inverse[N][N] = {0};

struct param{
    int i;
    int j;
    float det;
};

void cofactor(int a[N][N], int temp[N][N], int p, int q, int n) {

	int i=0,j=0;

	for (int row=0; row < n; row++) {
		
		for (int col=0; col < n; col++) {
			if (row != p && col != q) {
				temp[i][j++] = a[row][col];

				if (j == n-1) {
					j = 0;
					i++;
				}
			}
		}
	}
}

int det(int a[N][N], int n) {	
	if (n==1)
		return a[0][0];

	int temp[N][N];

	int sign = 1;

	int d = 0;

	for (int i = 0; i < n; i++) {
		cofactor(a, temp, 0, i, n);
		d += sign * a[0][i] * det(temp, n-1);

		sign = -sign;
	}

	return d;

}

void *cofactor_runner(void *param)
{
    struct param *p = param;
    int sign;
    int temp[N][N];

    if((p->i + p->j)%2 == 0){
        sign = 1;
    }
    else{
        sign = -1;
    }
    cofactor(mat, temp, p->i, p->j, N);
    inverse[p->j][p->i] = (sign*det(temp, N-1))/p->det;
    pthread_exit(0);
}

int main()
{
    printf("Enter the matrix: ");
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            scanf("%d", &mat[i][j]);
        }
    }
    int d = det(mat, N);

    pthread_t tid[N*N];
    pthread_attr_t attr;

    int counter=0;

    struct param *data = (struct param*)malloc(sizeof(struct param));

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            data->i = i;
            data->j = j;
            data->det = (float)d;
            pthread_attr_init(&attr);
            pthread_create(&tid[counter], &attr, &cofactor_runner, data);
            counter++;
        }
    }
    
    for(int i=0;i<counter;i++){
        pthread_join(tid[i], NULL); 
    }

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            printf("%f ", inverse[i][j]);
        }
        printf("\n");
    }
    return 0;
}