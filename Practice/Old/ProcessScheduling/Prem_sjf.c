#include<stdio.h>

typedef struct process{
    int pid,at,bt,rem_bt,wt,tat;
}process;

void prem_Scheduling(process processes[],int n){
    int completed=0, time=0, complete[n],minbt=10000,minIndex=-1;

    for(int i=0;i<n;i++){
        complete[i]=0;
        processes[i].rem_bt=processes[i].bt;
    }

    while(completed<n){
        minbt=10000;
        minIndex=-1;

        for(int i=0;i<n;i++){
            if(processes[i].at<=time && !complete[i] && processes[i].rem_bt<minbt){
                minbt=processes[i].rem_bt;
                minIndex=i;
            }
        }

        if(minIndex==-1){
            time++;
            continue;
        }

        processes[minIndex].rem_bt--;
        time++;

        if(processes[minIndex].rem_bt==0){
            completed++;
            complete[minIndex]=1;
            processes[minIndex].tat=time-processes[minIndex].at;
            processes[minIndex].wt=processes[minIndex].tat-processes[minIndex].bt;
        }
    }
}

void printProcess(process processes[],int n){
    printf("The processes with there pid, arrival time, burst time, wait time and turn around time are: \n");
    for(int i=0;i<n;i++){
        printf("Process %d:\t%d\t%d\t%d\t%d\n",processes[i].pid,processes[i].at,processes[i].bt,processes[i].wt,processes[i].tat);
    }
}

int main(){
    int n;
    printf("Enter the number of Processes: ");
    scanf("%d",&n);
    process processes[n];

    for(int i=0;i<n;i++){
        processes[i].pid=i+1;
    }

    printf("Enter the arrival time and burst time for the processes\n");
    for(int i=0;i<n;i++){
        printf("Process %d",processes[i].pid);
        scanf("%d%d",&processes[i].at,&processes[i].bt);
    }

    prem_Scheduling(processes,n);
    printProcess(processes,n);
    return 0;
}
