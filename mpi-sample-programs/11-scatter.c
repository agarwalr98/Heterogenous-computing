#include <stdio.h>
#include <mpi.h>
#define SIZE 4

int main(int argc,char *argv[])
{
	int my_rank, num_process;
	int sendcount, recvcount, source;
	float sendbuf[SIZE][SIZE] = {
  		{1.0, 2.0, 3.0, 4.0},
  		{5.0, 6.0, 7.0, 8.0},
  		{9.0, 10.0, 11.0, 12.0},
  		{13.0, 14.0, 15.0, 16.0}  };
	float recvbuf[SIZE];

	/*....MPI Initialisation....*/
    MPI_Init(&argc, &argv); // Initialise MPI
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); // Get my rank
	MPI_Comm_size(MPI_COMM_WORLD, &num_process); // Get the total number of processors

	if (num_process == SIZE) {
  		source = 1;
  		sendcount = SIZE;
  		recvcount = SIZE;
  		MPI_Scatter(sendbuf,sendcount,MPI_FLOAT,recvbuf,recvcount, MPI_FLOAT,source,MPI_COMM_WORLD);

  		printf("Process = %d - Results: %f %f %f %f\n",my_rank, recvbuf[0],recvbuf[1],recvbuf[2],recvbuf[3]);
  	}
	else
  	printf("Must specify %d processors. Terminating.\n",SIZE);

	MPI_Finalize();
}


