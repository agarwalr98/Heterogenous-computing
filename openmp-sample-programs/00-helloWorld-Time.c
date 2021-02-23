/* Hello World Serial program */
#include <stdio.h>
#include <time.h>

int main ()
{
	int j;	
	double total_time;
	clock_t start, end;
	start=clock();
	srand(time(NULL));
	for(j=0;j<4;j++)
		printf("Hello World!\n");

	end=clock;
	total_time=((double) (end-start));
	printf("Time taken = %f\n", total_time);
	return 0;
}
