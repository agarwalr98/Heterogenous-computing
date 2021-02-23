#include <stdio.h>
#include <mpi.h>

int main(int argc,char *argv[])
{
    int my_rank, size, Root=0;
	int val, s=0, sum=0;
    MPI_Status status;

    	/*....MPI Initialisation....*/

    MPI_Init(&argc, &argv); // Initialise MPI
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); // Get my rank
	MPI_Comm_size(MPI_COMM_WORLD, &size); // Get the total number of processors

	if(my_rank == Root){
		printf("\nEnter the value to be broadcasted : ");
		scanf("%d",&val);
    }
    	
	/*....Broadcast the value to each processor....*/ 

   	MPI_Bcast(&val, 1, MPI_INT, Root, MPI_COMM_WORLD);
	s=val+my_rank;
	printf("   Process %d: val = %d, sum = %d\n", my_rank, val, s);

	/*....The REDUCE function of MPI....*/
    	MPI_Reduce(&val, &sum, 1, MPI_INT, MPI_SUM, Root, MPI_COMM_WORLD);

    	if(my_rank == Root)
		 printf("\nReduction - Process %d: SUM = %d\n", my_rank, sum);

	/*....The REDUCE function of MPI....*/
    	MPI_Reduce(&s, &sum, 1, MPI_INT, MPI_SUM, Root, MPI_COMM_WORLD);

    	if(my_rank == Root) 
		 printf("\nReduction - Process %d: SUM = %d\n", my_rank, sum);

//	printf("Process %d is done.\n", my_rank);
	fflush (stdout);
    	MPI_Finalize();
}

