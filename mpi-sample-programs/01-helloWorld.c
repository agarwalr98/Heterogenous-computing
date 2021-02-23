#include <stdio.h>
#include <mpi.h>

void main (int argc, char *argv[])
{
	int err;
	MPI_Init(&argc, &argv);		// Initialise MPI
	printf("Hello World!\n");
	MPI_Finalize();			// Terminate MPI
}
