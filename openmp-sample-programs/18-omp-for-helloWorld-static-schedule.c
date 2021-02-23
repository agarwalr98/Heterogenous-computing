/* Hello World Parallel for program with illustarion to static schedule clause */
#include <stdio.h>
#include <omp.h>   // Header file for OpenMP

int main ()
{
	/* Serial Section */
	int i, j;
	
	/*******************/

	/* Parallel Section */
//	#pragma omp parallel for private(i) schedule(static)
	#pragma omp parallel for private(i) schedule(static, 2)
    	for (j=0; j<10; j++)
	{
			i=omp_get_thread_num();
        		printf("Hello World from thread %d, Iteration %d\n",i,j);
	
    	}
	/*******************/

    	/* Serial Section */
    	return 0;
	/*******************/
}
