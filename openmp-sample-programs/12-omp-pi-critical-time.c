/* Estimating value of pi using a form of numerical integration - rectangle rule */
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <omp.h>   // Header file for OpenMP

int main ()
{
	/* Serial Section */
	int i, j, n, t;
	double area, pi, x;
	double PI25DT = 3.141592653589793238462643;

	clock_t start, end;
     	double cpu_time_used;

	printf("Enter the value for n: ");
	scanf("%d", &n);
	printf ("Ennter the number of threads: ");
	scanf("%d", &t);

	omp_set_num_threads(t);  // Set the number of threads

	area=0.0;
	start = clock();
	/*******************/

	/* Parallel Section */
	#pragma omp parallel for private(x)
    	for (j=0; j<n; j++)
	{
//			i = omp_get_thread_num();
			x = (j+0.5)/n;
		/* Critical Section */
		#pragma omp critical
		{
			area += 4.0/(1.0 + x*x);
		}
		/*******************/
	
    	}
	/*******************/

    	/* Serial Section */
	pi = area/n;
	end = clock();
     	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
//	printf("pi is approximately %.16f, Error is %.16f\n",pi, fabs(pi - PI25DT));
	printf("Number of Threads = %d : CPU time = %f\n", t, cpu_time_used);
    	return 0;
	/*******************/
}
