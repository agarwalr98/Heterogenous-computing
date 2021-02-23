/* Estimating value of pi using a form of numerical integration - rectangle rule */
#include <stdio.h>
#include <math.h>
#include <omp.h>   // Header file for OpenMP

int main ()
{
	/* Serial Section */
	int i, j, n=10000000;
	double area, pi, x;
	double PI25DT = 3.141592653589793238462643;

//	printf("Enter the value for n: ");
//	scanf("%d", &n);

	area=0.0;
	/*******************/

	/* Parallel Section */
	#pragma omp parallel for private(x)
    	for (j=0; j<n; j++)
	{
			i = omp_get_thread_num();
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
	printf("pi is approximately %.16f, Error is %.16f\n",pi, fabs(pi - PI25DT));
    	return 0;
	/*******************/
}
