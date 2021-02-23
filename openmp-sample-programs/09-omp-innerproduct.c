/* Computing Innerproduct */
#include <stdio.h>
#include <omp.h>   // Header file for OpenMP

int main ()
{
	/* Serial Section */
	int i, j, n=10, x[10], y[10], s=0;

	for(j=0;j<n;j++){
		x[j]=j;
        	y[j]=j+1;
		printf("x[%d]=%d   y[%d]=%d\n",j,x[j],j,y[j]);
	}
	printf("-------------------------\n");
	/*******************/

	/* Parallel Section */
	#pragma omp parallel for private(i) reduction(+:s)
    for (j=0; j<10; j++)
	{
		i=omp_get_thread_num();
		s=s+(x[j]*y[j]);
			printf("Thread %d --> x[%d]=%d, y[%d]=%d: IntermediateSum = %d\n",i,j,x[j],j,y[j], s);

    }
	/*******************/

    /* Serial Section */
	printf("\nSerial: Innerproduct = %d\n",s);
    	return 0;
	/*******************/
}
