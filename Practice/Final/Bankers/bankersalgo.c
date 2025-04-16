#include<stdio.h>

int main(){
    int p,r;
    printf("Enter the number of processes: ");
    scanf("%d",&p);
    printf("Enter the number of resources: ");
    scanf("%d",&r);

    int allocated[p][r];
    int max[p][r];
    int need[p][r];
    int available[r];
    int work[r];

    printf("Enter the allocated matrix:\n");
    for(int i=0;i<p;i++){
        for(int j=0;j<r;j++){
            printf("Element %d %d: ",i,j);
            scanf("%d",&allocated[i][j]);
        }
    }

    printf("Enter the max matrix:\n");
    for(int i=0;i<p;i++){
        for(int j=0;j<r;j++){
            printf("Element %d %d: ",i,j);
            scanf("%d",&max[i][j]);
        }
    }

    for(int i=0;i<p;i++){
        for(int j=0;j<r;j++){
            need[i][j]=max[i][j]-allocated[i][j];
        }
    }

    printf("Enter available Resources:\n");
    for(int i=0;i<r;i++){
        printf("Resource %d: ",i);
        scanf("%d",&available[i]);
    }

    int finish[p];
    for(int i=0;i<p;i++){
        finish[i]=0;
    }

    for(int i=0;i<r;i++){
        work[i]=available[i];
    }

    int safeSeq[p];
    int count=0;

    while(count < p){
        int found=0;
        for(int i=0;i<p;i++){
            if(finish[i]==0){
                int canAllocate=1;
                for(int j=0;j<r;j++){
                    if(need[i][j]>work[j]){
                        canAllocate=0;
                        break;
                    }
                }
                if(canAllocate){
                    for(int j=0;j<r;j++){
                        work[j]+=allocated[i][j];
                    }
                    safeSeq[count++]=i;
                    finish[i]=1;
                    found=1;
                }
            }
        }
        if(!found){
            printf("Not a safe Sequece!\n");
            return 1;
        }
    }
    printf("System is in safe state:\n");
    for(int i=0;i<p;i++){
        printf("P%d ",safeSeq[i]);
    }
    printf("\n");
    return 0;
}
