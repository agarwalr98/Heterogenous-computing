#include <stdio.h>
#include <mpi.h>

void main (int argc, char *argv[])
{
	int my_rank, size;
	MPI_Init(&argc, &argv); // Initialise MPI
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); // Get my rank
	MPI_Comm_size(MPI_COMM_WORLD, &size); // Get the total number of processors

	printf("Greetings from Processor %d of %d.\n", my_rank, size);
	MPI_Finalize(); // Terminate MPI
}
