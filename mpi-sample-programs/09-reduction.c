#include <stdio.h>
#include <mpi.h>

int main(int argc,char *argv[])
{
    	int my_rank, size, Root=0;
	int sum = 0;
    	MPI_Status status;

    	/*....MPI Initialisation....*/

    	MPI_Init(&argc, &argv); // Initialise MPI
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); // Get my rank
	MPI_Comm_size(MPI_COMM_WORLD, &size); // Get the total number of processors

    	/*....The REDUCE function of MPI....*/

    	MPI_Reduce(&my_rank, &sum, 1, MPI_INT, MPI_SUM, Root, MPI_COMM_WORLD);

    	if(my_rank == Root) 
		 printf("   Process %d: SUM = %d\n", my_rank, sum);

	printf("Process %d is done.\n", my_rank);
	fflush (stdout);
    	MPI_Finalize();
}

