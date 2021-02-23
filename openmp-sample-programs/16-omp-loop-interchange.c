#include<stdio.h>
#include <time.h>
#include <omp.h>   // Header file for OpenMP

#define N 10

int main()
{

      /* Serial Section */
      int i,j,k;
      int a[N][N],b[N][N];
      clock_t start, end;
      double cpu_time_used;

      #pragma omp parallel for private(i,j)
      for(i=0;i<N;i++){
//	k = omp_get_thread_num();
       	for(j=0;j<N;j++){
          a[i][j]=i+1;
	  b[i][j]=i+1;
	  printf("(%d):%d  ", k, a[i][j]);
	}
	printf("\n");
      }

      start = clock();
      /*******************/

      /* Parallel Section */
      for(i=1;i<N;i++){
        #pragma omp parallel for private(j), firstprivate(i)
       	for(j=0;j<N;j++){
          a[i][j]=2*a[i-1][j];
	}
      }
      /*******************/

      end = clock();
      cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
      printf("CPU time = %f\n", cpu_time_used);

      printf("Updated matrix before loop interchange:\n");
      for(i=0;i<N;i++){
       	for(j=0;j<N;j++){
	  printf("%d\t", a[i][j]);
	}
	printf("\n");
      }
      printf("------------------------------------------\n");

      start = clock();
      #pragma omp parallel for private(i,j)
      for(j=0;j<N;j++){
       	for(i=1;i<N;i++){
          b[i][j]=2*b[i-1][j];
	}
      }
      end = clock();
      cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
      printf("CPU time (after loopinterchange)= %f\n", cpu_time_used);

      printf("Updated matrix after loop interchange:\n");
      for(i=0;i<N;i++){
       	for(j=0;j<N;j++){
	  printf("%d\t", b[i][j]);
	}
	printf("\n");
      }
 
 return 0;
}

