#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

void main (int argc, char *argv[])
{
	int my_rank, size;
	int a[100], b[100];
	int i, source, dest, count=10;
	MPI_Status status;

	MPI_Init(&argc, &argv); // Initialise MPI
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); // Get my rank
	MPI_Comm_size(MPI_COMM_WORLD, &size); // Get the total number of processors

	if (my_rank == 0)
	{
		dest=1;
		source=1;
		printf("Processor %d:\n", my_rank);
		/* Receive and then send message */
		MPI_Recv(&b, 100, MPI_INT, source, 7, MPI_COMM_WORLD, &status); // Receive message		
		MPI_Send(&a, 100, MPI_INT, dest, 5, MPI_COMM_WORLD); //Send message
	}
	else if (my_rank == 1)
	{
		source=0;
		dest=0;
		printf("Processor %d:\n", my_rank);
		/* Receive and then send message */
		MPI_Recv(&b, 100, MPI_INT, source, 5, MPI_COMM_WORLD, &status); // Receive message		
		MPI_Send(&a, 100, MPI_INT, dest, 7, MPI_COMM_WORLD); //Send message
	}
	printf("Processor %d is done.\n", my_rank);
	fflush (stdout);
	MPI_Finalize();
}
