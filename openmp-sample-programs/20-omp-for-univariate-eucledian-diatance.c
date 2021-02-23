/* Computing Eucledian distance between every pair of N univariate samples */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>   // Header file for OpenMP

#define N 10

int main ()
{
	
	int i, j, k;
	int x[N];
	double dist[N][N];
	clock_t start, end;
      	double cpu_time_used;

	#pragma omp parallel for
     	for(i=0;i<N;i++){
       		x[i]=(rand()%100)+1;
	}
	printf("x: ");
	for(i=0;i<N;i++){
	     printf("%d ", x[i]);
	     for(j=0;j<N;j++){
       		dist[i][j]=0.0;
	     }
      	}
	printf("\n");

	start = clock();
	#pragma omp parallel for private(k,j)
//	#pragma omp parallel for private(k,j) schedule(dynamic)
    	for (i=0; i<N; i++)
	{
		k=omp_get_thread_num();
		printf("Thread %d, Iteration %d\n",k,i);
		for (j=i; j<N; j++)
		{
			dist[i][j]=(x[i]-x[j])*(x[i]-x[j]);
		}
    	}
	end = clock();
      	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
      	printf("CPU time = %f\n", cpu_time_used);

	printf("Diatance Matrix: \n");
	for(i=0;i<N;i++){
	     for(j=0;j<N;j++){
       		printf("%6.2f\t", dist[i][j]);
	     }
	     printf("\n");
      	}
    	return 0;
	
}
