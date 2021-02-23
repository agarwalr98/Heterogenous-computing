#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_VALUE 10000000
#define fileName "prob1-input.text"
#define outputFile "prob1-output.text"

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

int readNumbers(int n, int Array[]){
    FILE* ptr = fopen(fileName,"r");
    int i=0, num=0;
    while(fscanf(ptr, "%d ", &num)!=EOF){
        Array[i] = num;
        i++;
    }
    fclose(ptr);
    return i;
}

//partition an array such that left to pivot elements are smaller than pivot &&
//right to pivot are greater than pivot.
int partition(int Array[],int low, int high){
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
    if (low<high){
        int partitionElement = partition(Array, low, high);
        quickSort(low, partitionElement-1, Array);
        quickSort(partitionElement+1, high, Array);
    }
}

void print(int n, int Array[]){
    if (n<10){
        printf("Sorted numbers are: \n");
        for(int i=0;i<n;i++)
            printf("%d ", Array[i]);
        printf("\n");
    }
}

int main(){
    printf("Enter value of n\n");
    int n;
    clock_t start, end;
    scanf("%d", &n);
    int Array[n];
    writeNumbers(n);
    n = readNumbers(n, Array);

    start = clock();
    quickSort(0, n-1, Array);
    end = clock();

    FILE* ptr = fopen(outputFile, "w+");
    for(int i=0;i<n;i++){
        fprintf(ptr, "%d ", Array[i]);
    }

    double total_time = ((double)(end-start))/CLOCKS_PER_SEC;
    printf("-------------------------------------\n");
    printf("Total time taken %lf s\n", total_time);
    printf("-------------------------------------\n");
    return 0;
}
