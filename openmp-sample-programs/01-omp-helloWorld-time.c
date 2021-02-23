/* Hello World Serial program */
#include <stdio.h>
#include <time.h>
#include <omp.h>   // Header file for OpenMP

int main ()
{
	/* Serial Section */
	int i;
	double total_time;
	clock_t start, end;
	start=clock();
	srand(time(NULL));
	/*******************/

	/* Parallel Section */
	#pragma omp parallel private(i)
    	{        	
		i=omp_get_thread_num();
        	printf("Hello World from thread %d\n",i);
    	}
	/*******************/

    	/* Serial Section */
	end=clock();
	total_time=((double) (end-start));
	printf("Time taken = %f\n", total_time);
    	return 0;
	/*******************/
}
