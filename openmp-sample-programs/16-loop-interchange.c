#include<stdio.h>
#include <time.h>

#define N 10

int main()
{

      int i,j,k;
      int a[N][N],b[N][N];
      clock_t start, end;
      double cpu_time_used;

      for(i=0;i<N;i++){
       	for(j=0;j<N;j++){
          a[i][j]=i+1;
	  b[i][j]=i+1;
	  printf("%d\t", a[i][j]);
	}
	printf("\n");
      }

      start = clock();
      for(i=1;i<N;i++){
       	for(j=0;j<N;j++){
          a[i][j]=2*a[i-1][j];
	}
      }
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

      start = clock();
      for(j=0;j<N;j++){
       	for(i=1;i<N;i++){
          b[i][j]=2*b[i-1][j];
	}
      }
      end = clock();
      cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
      printf("CPU time (loop interchange) = %f\n", cpu_time_used);

      printf("Updated matrix after loop interchange:\n");
      for(i=0;i<N;i++){
       	for(j=0;j<N;j++){
	  printf("%d\t", b[i][j]);
	}
	printf("\n");
      }
 
 return 0;
}

