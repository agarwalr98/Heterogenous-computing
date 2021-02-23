#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

void main (int argc, char *argv[])
{
	int my_rank, size;
	char message[100];
	int source, dest, tag=1;
	MPI_Status status;

	MPI_Init(&argc, &argv); // Initialise MPI
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); // Get my rank
	MPI_Comm_size(MPI_COMM_WORLD, &size); // Get the total number of processors

	if (my_rank !=0)
	{
		sprintf(message, "Greetings from Preocessor %d of %d!", my_rank, size);
		dest=0;
		MPI_Send(message, strlen(message)+1, MPI_CHAR, dest, tag, MPI_COMM_WORLD); //Send message
	}
	else // rank = 0
	{
		printf("Receiving greeting at Processor %d:\n",my_rank);
		for (source=1; source<size; source++)
		{
			MPI_Recv(message, 100, MPI_CHAR, source, tag, MPI_COMM_WORLD, &status); // Receive message
			printf("\t%s\n", message);
		}
	}
	MPI_Finalize(); // Terminate MPI
}
