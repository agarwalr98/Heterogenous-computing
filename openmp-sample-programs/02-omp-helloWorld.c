/* Hello World Parallel program with multiple parallel sections and setting different threads for each parallel section */
#include <stdio.h>
#include <omp.h>   // Header file for OpenMP

int main ()
{
	/* Serial Section */
	int i, t;

	t = omp_get_num_procs(); // Get the number of physical processors
	omp_set_num_threads(t);  // Set the number of threads

	printf("Number of thereads = %d\n", t);
	/********************/

	/* Parallel Section */
	#pragma omp parallel private(i)
    	{        	
		i=omp_get_thread_num();
        	printf("Hello World from thread %d\n",i);
    	}
	/********************/

	/* Serial Section */
	printf("-------------------------\n");
	t = 3;
	omp_set_num_threads(t);  // Set the number of threads

	printf("Number of thereads = %d\n", t); 
	/********************/

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
