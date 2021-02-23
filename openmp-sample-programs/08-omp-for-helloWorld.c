/* Hello World Parallel for program with illustarion to reduction clause */
#include <stdio.h>
#include <omp.h>   // Header file for OpenMP

int main ()
{
	/* Serial Section */
	int i, j, k=0;
	printf("\nSerial: thread %d, Iteration %d, k = %d\n\n",i,j, k);
	/*******************/

	/* Parallel Section */
	#pragma omp parallel for private(i) reduction(+:k)
    	for (j=0; j<10; j++)
	{
			i=omp_get_thread_num();
			k++;
        		printf("Hello World from thread %d, Iteration %d: k = %d\n",i,j, k);
	
    	}
	/*******************/

    	/* Serial Section */
	printf("\nSerial: thread %d, Iteration %d, k = %d\n",i,j, k);
	printf("Serial: Sum = %d\n",k);
    	return 0;
	/*******************/
}
