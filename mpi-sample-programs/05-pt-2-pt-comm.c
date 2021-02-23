#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

void main (int argc, char *argv[])
{
	int my_rank, size;
	int a[100], b[100], n;
	int i, source, dest, tag=1, count;
	MPI_Status status; 

	MPI_Init(&argc, &argv); // Initialise MPI
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); // Get my rank
	MPI_Comm_size(MPI_COMM_WORLD, &size); // Get the total number of processors
//	MPI_Barrier(MPI_COMM_WORLD);

	if (my_rank ==0)
	{
		printf("Enter the size of array: ");
		scanf("%d", &n);
		printf("Enter the %d elements :",n);
		for (i=0; i<n; i++)
			scanf("%d", &a[i]);		
		
		dest=1; 
		count=n;	
		MPI_Send(&a, count, MPI_INT, dest, tag, MPI_COMM_WORLD); //Send message
	}
	else if (my_rank == 1)
	{
		source=0;		
		MPI_Recv(&b, 5, MPI_INT, source, tag, MPI_COMM_WORLD, &status); // Receive message				
		printf("  Processor %d received %d values:", my_rank, count);
		for (i=0; i<5; i++)
			printf("%d ", b[i]);
		printf("\n");
		printf("Processor %d: n = %d ", my_rank, n);
	}
	printf("Process %d is done.\n", my_rank);
	fflush (stdout);
	MPI_Finalize();
}
