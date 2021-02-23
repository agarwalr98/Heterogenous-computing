#include <stdio.h>
#include <mpi.h>

int main (int argc, char *argv[]) {

int my_rank; 	/* Process rank */
int size;		/* Number of processes */
int i;
int a[10]={1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int b[10]={2, 4, 6, 8, 10, 1, 3, 5, 7, 9};
void mult(int, int, int);

MPI_Init (&argc, &argv);		// Initialise MPI
MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);	// Get my rank
MPI_Comm_size (MPI_COMM_WORLD, &size);	// Get the total number of processors

for (i=my_rank; i<10; i+=size)
	mult(my_rank, a[i], b[i]);
/*i=id;
mult(id, a[i], b[i]);*/

printf("Process %d is done.\n", my_rank);

fflush (stdout);
MPI_Finalize ();			// Terminate MPI
}

/* ------------------------- */
/* Multiplication subroutine */
/* ------------------------- */
void mult(int id, int x, int y){

int z;

z=x*y;

printf("(Process-%d) %d x %d = %d\n", id, x, y, z);
fflush (stdout);
}
