#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#define fileName "prob1-input.text"
#define outputFile "prob1-output.text"
#define MAX_VALUE 10000000
#define Maxsize 100000

int main(int argc, char *argv[]){

    double elapsed_time;
    int rank, numProcess, root=0, n;
    int Array[Maxsize], sortedArr[Maxsize];
    MPI_Init(&argc, &argv);   //Initializa Mpi
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   //get my rank
    MPI_Comm_size(MPI_COMM_WORLD, &numProcess);   //get number of processors

    // functions
    void writeNumbers(int);
    void readNumbers(int , int Array[]);
    int partition(int , int high, int Array[]);
    void quickSort(int low, int high, int Array[]);
    int getMinIndex(int, int, int, int pointer[], int Array[]);
    void print(int , int Array[]);

    if (rank == 0){

        printf("Enter value of n\n");
        scanf("%d", &n);
        writeNumbers(n);
        elapsed_time = - MPI_Wtime();
        readNumbers(n, Array);
    }
    
    MPI_Bcast(&n, 1, MPI_INT, root, MPI_COMM_WORLD);

    int localsize = n/numProcess;
    int scount[numProcess], dispals[numProcess];
    int recvCount[numProcess] ;
    for(int i=0;i<numProcess-1;i++){
        scount[i] = localsize;
        recvCount[i] = localsize;
        dispals[i] = i*localsize;
    }
    scount[numProcess-1] = localsize + n%numProcess; dispals[numProcess-1] = (numProcess-1)*localsize;
    recvCount[numProcess-1] = localsize + n%numProcess; dispals[numProcess-1] = (numProcess-1)*localsize;

    int low = localsize*rank, high = localsize*(rank+1);
    MPI_Bcast(&Array, n, MPI_INT, root, MPI_COMM_WORLD);

    if (rank == numProcess-1){
        high = n;
    }
    quickSort(low, high-1, Array);
    for(int i=low;i<high;i++){
        sortedArr[i-low] = Array[i];
    }
    MPI_Gatherv(&sortedArr, high-low, MPI_INT, &Array, recvCount, dispals, MPI_INT, root, MPI_COMM_WORLD);
    if (rank == root){
        int pointers[numProcess];
        for(int i=0;i<numProcess;i++){
            pointers[i] = localsize*i;
        }
        for(int i=0;i<n;i++){
            int minIndex = getMinIndex(n, numProcess, localsize, pointers, Array);
            
            sortedArr[i] = Array[pointers[minIndex]];
            pointers[minIndex]+=1;
        }

        print(n, sortedArr);
        //Write the results into a file.
        FILE* ptr = fopen(outputFile, "w+");
        for(int i=0;i<n;i++){
            fprintf(ptr, "%d ", sortedArr[i]);
        }

        elapsed_time+=MPI_Wtime();
        printf("---------------------------\n");
        printf("Total time taken: %lf\n", elapsed_time);
        printf("---------------------------\n");
    
    }
    
    fflush(stdout);
    MPI_Finalize();

    return 0;
}

//get the index of minimum element from the processors.
int getMinIndex(int n, int numProcess, int localize, int pointer[], int Array[]){
    int min = MAX_VALUE, minIndex = 0;
    for(int i=0;i<numProcess-1;i++){
        if (pointer[i]==-1){
            //
        }
        else if (pointer[i]>= (i+1)*localize){
            pointer[i] = -1;
        }
        else if (Array[pointer[i]]<min){
            min = Array[pointer[i]];
            minIndex = i;
        }
    }

    if (pointer[numProcess-1]!=-1 && pointer[numProcess-1] < n){
        if (Array[pointer[numProcess-1]] < min){
            minIndex = numProcess-1;
        }
    }
    else{
        pointer[numProcess-1] = -1;
    }

    return minIndex;
}

void writeNumbers(int n){

    FILE* ptr;
    ptr = fopen(fileName, "w+");
    if (ptr == NULL){
        printf("file is not opened!\n");
        return ;
    }
    else{
        printf("file is opened successfully!\n");
        for(int i=0;i<n;i++){

            fprintf(ptr, "%d ",rand()%MAX_VALUE);
        }
        printf("Generated %d random numbers into a file\n", n);
    }
    fclose(ptr);

}

void readNumbers(int n, int Array[]){
    FILE* ptr = fopen(fileName,"r");
    int i=0, num=0;
    while(fscanf(ptr, "%d ", &num)!=EOF){
        Array[i] = num;
        i++;
    }
    fclose(ptr);

}

//partition an array such that left to pivot elements are smaller than pivot &&
//right to pivot are greater than pivot.
int partition(int low, int high, int Array[]){
    int pivot = Array[high];
    int i=low-1,j=low;
    for(j=j;j<high;j++){
        if (Array[j]<pivot){
            i++;
            //swap
            int temp = Array[i];
            Array[i] = Array[j];
            Array[j] = temp;
        }
        
    }
    //last Element swap
    int temp = Array[high];
    Array[high] = Array[i+1];
    Array[i+1] = temp;

    return i+1;
}

void quickSort(int low, int high, int Array[]){
    //single element is already sorted.
    if (low<high){
        int partitionElement = partition(low, high, Array);
        quickSort(low, partitionElement-1, Array);
        quickSort(partitionElement+1, high, Array);
    }
}

void print(int n, int Array[]){
    if (n<10){
        printf("------------------------------\n");
        printf("Sorted numbers are: \n");
        for(int i=0;i<n;i++)
            printf("%d ", Array[i]);
        printf("------------------------------\n");
    }
}
