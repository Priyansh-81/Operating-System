#include<stdio.h>
#include<stdlib.h>

typedef struct{
    int id, size,allocated;
}process;

typedef struct{
    int id, size;
}hole;

void firstfit(process processes[], hole holes[], int np, int nh){
    for(int i=0; i<np;i++){
        for(int j=0;j<nh;j++){
            if(processes[i].size <= holes[j].size){
                processes[i].allocated=holes[j].id;
                holes[j].size-=processes[i].size;
                break;
            }
        }
    }
}

void bestfit(process processes[], hole holes[], int np,int nh){
    for(int i=0;i<np;i++){
        int bestindex=-1;
        for(int j=0;j<nh;j++){
            if(holes[j].size>=processes[i].size){
                if(bestindex==-1||holes[j].size<holes[bestindex].size){
                    bestindex=j;
                }
            }
        }
        if(bestindex!=-1){
            processes[i].allocated=holes[bestindex].id;
            holes[bestindex].size-=processes[i].size;
        }
    }
}

void worstfit(process processes[],hole holes[], int np, int nh){
    for(int i=0;i<np;i++){
        int worstindex=-1;
        for(int j=0;j<nh;j++){
            if(holes[j].size>=processes[i].size){
                if(worstindex==-1||holes[j].size>holes[worstindex].size){
                    worstindex=j;
                }
            }
        }
        if(worstindex!=-1){
            processes[i].allocated=holes[worstindex].id;
            holes[worstindex].size-=processes[i].size;
        }
    }
}

void printAllocation(process processes[], int np){
    printf("PID\tSize\tAllocateHole\n");
    for(int i=0;i<np;i++){
        if(processes[i].allocated!=-1){
            printf("%d\t%d\t%d\n",processes[i].id,processes[i].size,processes[i].allocated);
        }else{
            printf("%d\t%d\tNotAllocated\n",processes[i].id,processes[i].size);
        }
    }
}

int main(){
    int nh,np;
    printf("Enter the number of Holes: ");
    scanf("%d",&nh);
    printf("Enter the number of Processes: ");
    scanf("%d",&np);
    printf("Enter the size of the holes: \n");
    hole holes[nh],holes_copy[nh],holes_copy2[nh];
    process processes[np], processes_copy[np], processes_copy2[np];
    for(int i=0;i<nh;i++){
        holes[i].id=i+1;
        printf("Enter size of Hole %d: ",holes[i].id);
        scanf("%d",&holes[i].size);
        holes_copy2[i]=holes_copy[i]=holes[i];
    }
    printf("Enter the memory requirement for the processes\n");
    for(int i=0;i<np;i++){
        processes[i].id=i+1;
        printf("Enter mem req for %d: ", processes[i].id);
        scanf("%d",&processes[i].size);
        processes[i].allocated=-1;
        processes_copy2[i]=processes_copy[i]=processes[i];
    }
    printf("First fit\n");
    firstfit(processes,holes,np,nh);
    printAllocation(processes, np);
    printf("\nBest fit\n");
    bestfit(processes_copy,holes_copy,np, nh);
    printAllocation(processes_copy, np);
    printf("\nWorst fit\n");
    worstfit(processes_copy2,holes_copy2,np, nh);
    printAllocation(processes_copy2, np);
    return 0;
}
