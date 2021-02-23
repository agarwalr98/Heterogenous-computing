/* Hello World Parallel for program with illustarion to firstprivate clause */
#include <stdio.h>
#include <omp.h>   // Header file for OpenMP

int main ()
{
	/* Serial Section */
	int i, j, k=5;
	printf("\nSerial: thread %d, Iteration %d, k = %d\n\n",i,j, k);
	/*******************/

	/* Parallel Section */
	#pragma omp parallel for private(i) firstprivate(k)
    	for (j=0; j<10; j++)
	{
			i=omp_get_thread_num();
			k++;
        		printf("Hello World from thread %d, Iteration %d: k = %d\n",i,j, k);
	
    	}
	/*******************/

    	/* Serial Section */
	printf("\nSerial: thread %d, Iteration %d, k = %d\n",i,j, k);
    	return 0;
	/*******************/
}
