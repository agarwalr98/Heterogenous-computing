#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <time.h>
#define size 150

double getMean(int n, const double Array[]){
    double mean=0.0;
    #pragma omp parallel for reduction(+:mean)
    for(int j=0;j<n;j++)
    {
        mean = mean + Array[j];
    }

    mean = mean/n;
    return mean;
}

double getStdDev(int n, double mean, const double Array[])
{
    double stdDevSum=0.0;
    double StdDevArray[n];

    /* Method-1
        A single loop is parallelized in openmp, atomic is used for locking on the shared resources.
    */
    #pragma omp parallel for    
    for(int j=0;j<n;j++)
    {
        #pragma omp atomic
            stdDevSum += (Array[j]-mean)*(Array[j]-mean);
    }

    /* Method-2
        A single for loop is converted into two parallelizable codes to execute in openmp
    */
        // #pragma omp parallel for
        // for(int j=0;j<n;j++)
        // {
        //     StdDevArray[j] = (Array[j]-mean)*(Array[j]-mean);
        // }

        // #pragma omp parallel for reduction(+:stdDevSum)
        // for(int j=0;j<n;j++)
        // {
        //     stdDevSum+= StdDevArray[j];
        // }

    double stdDev =  (double)sqrt(stdDevSum/n);
    return stdDev;
}

double getZScore(double num, double mean, double stdDev){
    return ((num-mean)/stdDev);
}

int main(){
    double firstCol[size], secondCol[size], thirdCol[size], fourthCol[size];
    double Col[size][4];
    clock_t start, end;
    FILE* ptr = fopen("iris.data", "r");
    char str[1024];
    double col1, col2, col3, col4;
    double meanCol1=0, meanCol2=0, meanCol3=0, meanCol4=0;
    double stdCol1=0, stdCol2=0, stdCol3=0, stdCol4=0;
    int i=0;
    
    while(fgets(str,1024, ptr) != NULL){
        sscanf(str,"%lf,%lf,%lf,%lf,%s\n",&col1, &col2, &col3, &col4,str);
        firstCol[i]=col1;
        secondCol[i]=col2;
        thirdCol[i]=col3;
        fourthCol[i]=col4;
        i++;
    }
    fclose(ptr);

    //start time
    start = clock();

    //Loop unrolling is used here to avoid loop overhead for small loop (4 iterations)
    //Attribute1: first column
    meanCol1 = getMean(i, firstCol);
    stdCol1 = getStdDev(i, meanCol1, firstCol);
    
    //Attribute2: second Column
    meanCol2 = getMean(i, secondCol);
    stdCol2 = getStdDev(i, meanCol2, secondCol);

    //Attribute3: third Column
    meanCol3 = getMean(i, thirdCol);
    stdCol3 = getStdDev(i, meanCol3, thirdCol);

    //Attribute4: fourth column
    meanCol4 = getMean(i, fourthCol);
    stdCol4 = getStdDev(i, meanCol4, fourthCol);

    #pragma omp parallel for
    for(int i=0;i<size;i++)
    {
        Col[i][0] = getZScore(firstCol[i], meanCol1, stdCol1);
        Col[i][1] = getZScore(secondCol[i], meanCol2, stdCol2);
        Col[i][2] = getZScore(thirdCol[i], meanCol3, stdCol3);
        Col[i][3] = getZScore(fourthCol[i], meanCol4, stdCol4);
        // int thread = omp_get_thread_num();
        // printf("Thread %d iteration is %d\n", thread, i);
    }
    
    //end time
    end = clock();

    //File output
    printf("Result is saved in iris-Normalised.data\n");
    ptr = fopen("iris-Normalised.data", "w+");
    for(int i=0;i<size;i++){
        snprintf(str, 1024, "%.2f,%.2f,%.2f,%.2f\n", Col[i][0], Col[i][1], Col[i][2], Col[i][3]);
        fputs(str, ptr);
    }

    double total_time = ((double)(end-start))/CLOCKS_PER_SEC;
    printf("--------------------------------------\n");
    printf("Total time taken %lf\n", total_time);
    printf("--------------------------------------\n");
    
}
