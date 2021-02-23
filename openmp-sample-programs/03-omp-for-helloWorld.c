/* Hello World Parallel program with for loop in parallel section */
#include <stdio.h>
#include <omp.h>   // Header file for OpenMP

int main ()
{
	/* Serial Section */
	int i, j;
	/*******************/

	/* Parallel Section */
	#pragma omp parallel private(i)
    {       
	 	for (j=0; j<10; j++){
			i=omp_get_thread_num();
    		printf("Hello World from thread %d, Iteration %d\n",i,j);
		}
	}
	/*******************/

    	/* Serial Section */
    	return 0;
	/*******************/
}
