/* Hello World Serial program */
#include <stdio.h>
#include <omp.h>   // Header file for OpenMP

int main ()
{
	/* Serial Section */
	int i;
	/*******************/

	/* Parallel Section */
	#pragma omp parallel private(i)
    	{        	
		i=omp_get_thread_num();
        	printf("Hello World from thread %d\n",i);
    	}
	/*******************/

    	/* Serial Section */
    	return 0;
	/*******************/
}
