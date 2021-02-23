#include <stdio.h>
#include <math.h>
#include <time.h>
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

float getEuclidDistance(int n,float centroid[],float point[]){
    float distance = 0.0;
    for (int i=0;i<n;i++){
        distance = distance + (point[i]-centroid[i])*(point[i]-centroid[i]);
    }

    return (float)sqrt(distance);
}

int getClosestCluster(int K, float centroids[][numCols], float point[]){
    int cluster =-1;
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


int main(){
    
    int K=Clusters;        //Number of clusters
    printf("Number of clusters %d\n", K);
    float clusterCenters[K][4];
    float clusterSize[K];
    float clusterPoints[size][5];
    FILE* ptr = fopen("iris.data", "r");
    char str[1024];
    float col1, col2, col3, col4;
    int i=0;
    clock_t start, end;
    
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

    start = clock();
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
        for(int i=0;i<size;i++){
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

        for(int i=0;i<size;i++){
            int cluster = (int)clusterPoints[i][4];
            clusterSize[cluster]++;
            for(int j=0;j<numCols;j++){
                clusterCenters[cluster][j] += clusterPoints[i][j];
            }
        }

        for(int i=0;i<K;i++){

            clusterCenters[i][0] /= clusterSize[i];
            clusterCenters[i][1] /= clusterSize[i];
            clusterCenters[i][2] /= clusterSize[i];
            clusterCenters[i][3] /= clusterSize[i];
        }

        
    }

    end = clock();

    //Prompt out clusters if exists
    for(int i=0;i<K;i++){
        if (clusterSize[i]!=0)
            printf("cluster %d: (%f,%f,%f,%f )\n",i, clusterCenters[i][0], clusterCenters[i][1], clusterCenters[i][2], clusterCenters[i][3]);
        else
        {
            printf("cluster %d: does not exist (No vector is associated)\n", i);
        }
        
    }
    double total_time = (double)(end-start)/CLOCKS_PER_SEC;
    printf("-------------------------------------\n");
    printf("Total time taken %lf s \n", total_time);
    printf("----------------------------------------\n");

    return 0;
}

