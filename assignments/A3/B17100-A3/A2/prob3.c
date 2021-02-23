#include <stdio.h>
#include <math.h>
#include <mpi.h>
#define size 150
#define numCols 4
#define INT_MIN -999999
#define INT_MAX 9999999
#define Clusters 5

float absFloat(float a){
    if (a>0)
        return a;
    else return -a;

}

//get Euclid distance 
float getEuclidDistance(int n,float centroid[],float point[]){
    float distance = 0.0;
    for (int i=0;i<n;i++){
        distance = distance + (point[i]-centroid[i])*(point[i]-centroid[i]);
    }

    return (float)sqrt(distance);
}

//get closest cluster to each point
int getClosestCluster(int K, float centroids[][numCols], float point[]){
    int cluster =0;
    float distance = INT_MAX;
    for(int j=0;j<K;j++){
        float temp = getEuclidDistance(numCols, centroids[j], point);
        if (temp<distance){
            distance = temp;
            cluster = j;
        }
    }

    //the cluster index to which the item belongs to.
    return cluster;
}

//Main Function
int main(int argc, char *argv[]){
    
    double elapsed_time;
    int rank, numProcess;
    int K=Clusters, root=0;
    printf("NUmber of clusters %d\n", K);
    float clusterCenters[size][4];
    int clusterSize[size], recvSize[size];
    float clusterPoints[size][5],points[size][5];
    char str[1024];
    MPI_Init(&argc, &argv);   //Initializa Mpi
    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   //get my rank
    MPI_Comm_size(MPI_COMM_WORLD, &numProcess);   //get number of processors

    int count = (size/numProcess);

    if (rank == 0){


        FILE* ptr = fopen("iris.data", "r");
        float col1, col2, col3, col4;
        int i=0;
        while(fgets(str,1024, ptr) != NULL){
            sscanf(str,"%f,%f,%f,%f,%s\n",&col1, &col2, &col3, &col4,str);
            clusterPoints[i][0] = col1;
            clusterPoints[i][1] = col2;
            clusterPoints[i][2] = col3;
            clusterPoints[i][3] = col4;
            clusterPoints[i][4] = 0;   //Assigned to 0th cluster initially
            i++;
        }
        fclose(ptr);
    }

    //starting time
    elapsed_time = - MPI_Wtime();

    MPI_Bcast(&K, 1, MPI_INT, root, MPI_COMM_WORLD);
    int low = (size/numProcess)*rank, high = (size/numProcess)*(rank+1);
    if (rank == numProcess-1){
        high = size;
    }
    MPI_Bcast(&clusterPoints, size*5, MPI_FLOAT, root, MPI_COMM_WORLD);
    //Initialization of cluster centers
    for(int i=0;i<K;i++){
        clusterCenters[i][0] = clusterPoints[i][0];
        clusterCenters[i][1] = clusterPoints[i][1];
        clusterCenters[i][2] = clusterPoints[i][2];
        clusterCenters[i][3] = clusterPoints[i][3];
    }

    //Initially size of each cluster 0
    for(int i=0;i<K;i++)
        clusterSize[i]=0;

    // K means
    int noChange = 0;
    while(!noChange){
        
        noChange =1;
        //get the closest cluster for each point
        for(int i=low;i<high;i++){
            int clusterIndex = getClosestCluster(K, clusterCenters, clusterPoints[i]);
            if (clusterIndex!=(int)clusterPoints[i][4]){
                clusterPoints[i][4]= clusterIndex;
                noChange = 0;
            }
        }
        
        for(int i=0;i<K;i++){
            clusterSize[i]=0;
            clusterCenters[i][0]=0.0;
            clusterCenters[i][1]=0.0;
            clusterCenters[i][2]=0.0;
            clusterCenters[i][3]=0.0;
        }

        for(int i=low;i<high;i++){
            int cluster = (int)clusterPoints[i][4];
            clusterSize[cluster]++;
            for(int j=0;j<numCols;j++){
                clusterCenters[cluster][j] += clusterPoints[i][j];
            }
        }
        MPI_Barrier(MPI_COMM_WORLD);
        MPI_Allreduce(MPI_IN_PLACE, &clusterSize, K, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
        MPI_Allreduce(MPI_IN_PLACE, &clusterCenters ,K*4, MPI_FLOAT, MPI_SUM, MPI_COMM_WORLD);
        for(int i=0;i<K;i++){

            clusterCenters[i][0] /= clusterSize[i];
            clusterCenters[i][1] /= clusterSize[i];
            clusterCenters[i][2] /= clusterSize[i];
            clusterCenters[i][3] /= clusterSize[i];
        }
        MPI_Allreduce(MPI_IN_PLACE, &noChange, 1, MPI_INT, MPI_BAND, MPI_COMM_WORLD);

    }

    //ending time
    elapsed_time+=MPI_Wtime();

    if (rank == root){
    //Prompt out clusters if exists
        for(int i=0;i<K;i++){
            if (clusterSize[i]!=0)
                printf("cluster %d: (%f,%f,%f,%f )\n",i, clusterCenters[i][0], clusterCenters[i][1], clusterCenters[i][2], clusterCenters[i][3]);
            else
            {
                printf("cluster %d: does not exist (No vector is associated)\n", i);
            }
            
        }

        printf("---------------------------\n");
        printf("Total time taken: %lf s\n", elapsed_time);
        printf("---------------------------\n");
    
    }

    
    fflush(stdout);
    MPI_Finalize();
    return 0;
}

