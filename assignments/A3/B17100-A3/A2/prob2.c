#include <stdio.h>
#include <math.h>
#include <mpi.h>
#define size 150


int main(int argc, char *argv[]){

    double elapsed_time;
    int i=0, rank, numProcess, root =0, tag=1;
    MPI_Status status;
    double ColumnVectors[4][size];
    double Col[size], recvCol[4][size], recvSecondCol[size], recvThirdCol[size], recvFourthCol[size];
    char str[1024];
    double recvBuffer[size], global_sum=0;
    double col1, col2, col3, col4;
    double meanCol1=0, meanCol2=0, meanCol3=0, meanCol4=0;
    double stdCol1=0, stdCol2=0, stdCol3=0, stdCol4=0;

    //functions
    double getSum(int , int , const double Array[]);
    double getSquareSum(int ,int, double, const double Array[]);
    double getZScore(double, double, double);

    MPI_Init(&argc, &argv);   //Initializa Mpi
    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   //get my rank
    MPI_Comm_size(MPI_COMM_WORLD, &numProcess);   //get number of processors

    int recvCounts[numProcess], dispals[numProcess];
    int count = size/numProcess;
    int stride = count;
    for(i=0;i<numProcess-1;i++){
        recvCounts[i]=count;
        dispals[i] = i*stride;
    }
    recvCounts[i] = count + (size%numProcess);
    dispals[i] = i*stride;
    i=0;
    if (rank == root){
        FILE* ptr = fopen("iris.data", "r");
        while(fgets(str,1024, ptr) != NULL){
            sscanf(str,"%lf,%lf,%lf,%lf,%s\n",&col1, &col2, &col3, &col4,str);
            ColumnVectors[0][i] = col1;
            ColumnVectors[1][i] = col2;
            ColumnVectors[2][i] = col3;
            ColumnVectors[3][i] = col4;
            i++;
        }
        fclose(ptr);
    
    }


    //start time
    elapsed_time = - MPI_Wtime();

    MPI_Bcast(&ColumnVectors[0], size, MPI_DOUBLE, root, MPI_COMM_WORLD);
    MPI_Bcast(&ColumnVectors[1], size, MPI_DOUBLE, root, MPI_COMM_WORLD);
    MPI_Bcast(&ColumnVectors[2], size, MPI_DOUBLE, root, MPI_COMM_WORLD);
    MPI_Bcast(&ColumnVectors[3], size, MPI_DOUBLE, root, MPI_COMM_WORLD);
    int low = (size/numProcess)*rank, high = (size/numProcess)*(rank+1);
    if (rank == numProcess-1){
        high = size;
    }
    for (int index=0;index<4;index++){
        /* Calculate Z score/Normalised */

        //Calculate mean
        double local_sum  = getSum(low, high, ColumnVectors[index]);
        MPI_Allreduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
        meanCol1 = global_sum/size;
        
        //calculate standard deviation
        local_sum = getSquareSum(low, high, meanCol1, ColumnVectors[index]);
        MPI_Allreduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
        stdCol1 = sqrt(global_sum/size);
        
        for(int i=low;i<high;i++){
            recvBuffer[i-low] = getZScore(ColumnVectors[index][i], meanCol1, stdCol1);
        }
        MPI_Gatherv(&recvBuffer, high-low, MPI_DOUBLE, &recvCol[index], recvCounts, dispals, MPI_DOUBLE, root, MPI_COMM_WORLD);
    
    }
    
    MPI_Barrier(MPI_COMM_WORLD);
    i = 0;

    //end time
    elapsed_time+=MPI_Wtime();

    if (rank == root){
        FILE* ptr = fopen("iris-Normalised.data", "w+");
        while(i!=size){
            snprintf(str,1024, "%.2f,%.2f,%.2f,%.2f\n", recvCol[0][i], recvCol[1][i], recvCol[2][i], recvCol[3][i]);
            fputs(str, ptr);
            i++;
        }

        printf("---------------------------\n");
        printf("Total time taken: %lf\n", elapsed_time);
        printf("---------------------------\n");

    }
    
    fflush(stdout);
    MPI_Finalize();
}

//get sum of subarray
double getSum(int low,int high, const double Array[]){
    double sum=0.0;
    for(int j=low;j<high;j++){
        sum = sum + Array[j];
    }
    return sum;
}

//get sum of square of difference of mean and value for suba
double getSquareSum(int low, int high,double mean, const double Array[])
{
    double squareSum=0.0;
    for(int j=low;j<high;j++){
        squareSum = squareSum + (Array[j]-mean)*(Array[j]-mean);
    }
    return squareSum;

}

double getZScore(double num, double mean, double stdDev){
    return ((num-mean)/stdDev);
}