#include <stdio.h>
#include <mpi.h>
// Bubble sort in the multiple processor. 
int main (int argc, char *argv[]) {

	int my_rank; 	/* Process rank */
	int size;		/* Number of processes */
	int i, j, n=12, my_first, my_last, s, Root=0;
	int a[12]={3, 6, 1, 8, 4, 9, 6, 5, 10, 2, 12, 0};
	int b[12];
	void insertionSort(int, int, int, int*);

	MPI_Init (&argc, &argv);		// Initialise MPI
	MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);	// Get my rank
	MPI_Comm_size (MPI_COMM_WORLD, &size);	// Get the total number of processors

	my_first = my_rank * n/size;
	my_last = (my_rank + 1) * n/size;
	s = my_last - my_first;
	printf("Process %d: First = %d, Last = %d\n", my_rank, my_first, my_last);

/*	j=0;
	for (i = my_first; i < my_last; i++) {
		b[j] = a[i];
		printf("(%d), b[%d] = %d; ", my_rank, j, b[j]);
		j=j+1;
	}
	printf("\n");*/

	MPI_Scatter(a, s, MPI_INT, b, s, MPI_INT, Root, MPI_COMM_WORLD);

	printf("Process %d: Size of array is %d. ", my_rank, s);
   	for (j=0; j<s; j++){
		printf("b[%d]=%d; ", j, b[j]);
   	}
   	printf("\n");

	insertionSort(my_rank, my_first, my_last, b);

	MPI_Gather(&b, s, MPI_INT, &a, s, MPI_INT, Root, MPI_COMM_WORLD);

	if (my_rank == Root)
	{
		printf("Sorted elements (%d): ", my_rank);
		for (j=0; j<n; j++){
			printf("%d ", a[j]);
   		}
		printf("\n");
	}
	printf("Process %d is done.\n", my_rank);
	fflush (stdout);
	MPI_Finalize ();			// Terminate MPI
}

void insertionSort(int id, int f, int l, int *b){

   int j, num, k, key;

   num=l-f;
   for (j=1; j<num; j++){
   	key = b[j];
	k=j-1;
	while ((k >= 0) && (b[k] > key)){
	    b[k+1]=b[k];
	    k=k-1;
	}
	b[k+1] = key;
   }
   
   printf("(Insertion) Process %d: Size of array is %d. ", id, num);
   for (j=0; j<num; j++){
	printf("b[%d]=%d; ", j, b[j]);
   }
   printf("\n");

   fflush (stdout);
}
