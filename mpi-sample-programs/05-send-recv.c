#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

void main (int argc, char *argv[])
{
	int my_rank, size;
	int a[10]={1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, b[5];
	int i, source, dest, tag=1, count=10;
	MPI_Status status;


	MPI_Init(&argc, &argv); // Initialise MPI
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); // Get my rank
	MPI_Comm_size(MPI_COMM_WORLD, &size); // Get the total number of processors

	if (my_rank == 0)
	{
		dest=1;
		MPI_Send(&a,          10,         MPI_INT,             dest,    tag,     MPI_COMM_WORLD); //Send message
	/*      MPI_Send (void *buff, int count, MPI_Datatype dtype, int dest, int tag, MPI_Comm comm); */
		printf("Preocess %d sending!\n", my_rank);
	}
	else // rank != 0
	{
		source=0;
		printf("Processor %d:\n", my_rank);
		if (my_rank == 1)
		{
		/* 	MPI_Recv (void *buff, int count, MPI_Datatype dtype, int source, int tag, MPI_Comm comm, MPI_Status *status);*/
			MPI_Recv(&b,              10,        MPI_INT,           source,     tag,  MPI_COMM_WORLD, &status); // Receive message		
			//MPI_Recv(&b, 5, MPI_INT, source, tag, MPI_COMM_WORLD, &status); // Receive message		
			printf("  Processor %d received:", my_rank);
			for (i=0; i<count; i++)
				printf("%d ", b[i]);
			printf("\n");
		}
		
	}
	fflush (stdout);
	MPI_Finalize();
}
