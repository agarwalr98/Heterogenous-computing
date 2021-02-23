#include <stdio.h>
#include <mpi.h>

int main (int argc, char *argv[]) {

	double sum, sum_local, elapsed_time;
	double a[256], b[256];
	int i, n, numprocs, myid, my_first, my_last;

	n = 256;

	/*....MPI Initialisation....*/
	MPI_Init(&argc, &argv);
	MPI_Barrier(MPI_COMM_WORLD);
	elapsed_time = - MPI_Wtime();
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);

	my_first = myid * n/numprocs;
	my_last = (myid + 1) * n/numprocs;
//	printf("Process %d: First = %d, Last = %d\n", myid, my_first, my_last);

	for (i = 0; i < n; i++) {
		a [i] = i * 0.5;
		b [i] = i * 2.0;
	}

	sum_local = 0;
	for (i = my_first; i < my_last; i++) {
		sum_local = sum_local + a[i]*b[i];
	}
//	printf("Process %d: Local sum = %f\n", myid, sum_local);
//	printf("--------------------------------------\n");

	//MPI_Allreduce(&sum_local, &sum, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
	MPI_Reduce(&sum_local, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	elapsed_time+=MPI_Wtime();
	if (myid==0) {
		printf ("sum = %f\n", sum);
		printf ("Time taken = %f\n", elapsed_time);
	}
	MPI_Finalize();

}
