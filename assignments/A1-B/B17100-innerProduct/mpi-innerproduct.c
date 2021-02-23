#include <stdio.h>
#include <mpi.h>
#define numSize 100000

int main(int argc, char *argv[]){

    double elapsed_time=0;
    int n, root=0; 
    int innerproduct=0, dotproduct=0;
    int x[numSize], y[numSize];
    int rank, size;
    MPI_Status status;
    MPI_Init(&argc, &argv);   //Initialize processors
    MPI_Barrier(MPI_COMM_WORLD);
    elapsed_time = - MPI_Wtime();
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   //get my rank
    MPI_Comm_size(MPI_COMM_WORLD, &size);   //get number of processors
    
    if (rank == root){                // Master Processor
        printf("Enter size of array\n");
        scanf("%d", &n);
        if (n%size!=0){
            printf("Must Specify Size of array as multiple of %d, Terminated.\n", size);
            return 0;
        }
        printf("Enter the %d values for array x\n", n);
        for(int i=0;i<n;i++){
            scanf("%d", &x[i]);
        }

        printf("Enter the %d values for array y\n", n);
        for(int i=0;i<n;i++){
            scanf("%d", &y[i]);
        }

    }
    MPI_Bcast(&n, 1, MPI_INT, root, MPI_COMM_WORLD);    //Broadcast value of n
    int recvX[n/size], recvY[n/size];                   //Array in each processor
    MPI_Scatter(&x, n/size, MPI_INT, recvX, n/size,MPI_INT, root, MPI_COMM_WORLD);      //Scatter x, y
    MPI_Scatter(&y, n/size, MPI_INT, recvY, n/size,MPI_INT, root, MPI_COMM_WORLD);         
    innerproduct =0;
    for(int i=0;i<(n/size);i++){
        innerproduct = innerproduct + recvX[i]*recvY[i]; 
    }

    MPI_Reduce(&innerproduct, &dotproduct, 1, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);  //Reduction to sum
    elapsed_time += MPI_Wtime();
    if (rank == root){
        printf("Dot product = %d\n", dotproduct);
        printf("total time taken is %f s\n", elapsed_time);
    }
    fflush(stdout);
    MPI_Finalize();
}