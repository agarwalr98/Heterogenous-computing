/*****************************************************************************
About: OpenMP program to multiply two matrices A and B and store into C matrix
*****************************************************************************/

#include<stdio.h>
#include <time.h>
#include <omp.h>   // Header file for OpenMP

#define N 100

int main()
{

      int i,j,k;
      double  a[N][N],b[N][N],c[N][N];
      clock_t start, end;
      double cpu_time_used;

      printf("\n    Simple Matrix Multiplication: N=%d\n\n",N);

#pragma omp parallel for private(k,j) 
     for(i=0;i<N;i++)
       for(j=0;j<N;j++)
        {
          a[i][j]=((i+2)*1.0)/(5.0+i*1.0);
          b[i][j]=((i+j)*1.0)/((j+1)*1.0);
          c[i][j]=0.0;
        }

     start = clock();
#pragma omp parallel for private(k,j) 
     for(i=0;i<N;i++)
       for(j=0;j<N;j++)
        for(k=0;k<N;k++)
           c[i][j] = c[i][j] + a[i][k]*b[k][j];
     end = clock();
     cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
     printf("CPU time (i,j,k)= %f\n", cpu_time_used);

     start = clock();
#pragma omp for private(k,j) 
     for(i=0;i<N;i++)
       for(k=0;k<N;k++)
        for(j=0;j<N;j++)
           c[i][j] = c[i][j] + a[i][k]*b[k][j];
     end = clock();
     cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
     printf("CPU time (i,k,j)= %f\n", cpu_time_used);



       printf("%lf\n",c[N-1][N-1]);

 return 0;
}

