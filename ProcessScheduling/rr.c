#include<stdio.h>

typedef struct process{
    int pid,at,bt,rem_bt,tat,wt;
}process;

void roundRobin(process processes[],int n, int quantum){
    int time=0;int completed=0;
    int complete[n];

    for(int i=0;i<n;i++){
        processes[i].rem_bt=processes[i].bt;
        complete[i]=0;
    }

    while(completed<n){
        int allIdle=1;

        for(int i=0;i<n;i++){
            if(processes[i].rem_bt>0){
                allIdle=0;
                if(processes[i].rem_bt>quantum){
                    time+=quantum;
                    processes[i].rem_bt-=quantum;
                }else{
                    time+=processes[i].rem_bt;
                    processes[i].tat=time-processes[i].at;
                    processes[i].wt=processes[i].tat-processes[i].bt;
                    complete[i]=1;
                    processes[i].rem_bt=0;
                    completed++;
                }
            }
        }
        if(allIdle){
            break;
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
    int n,quantum;
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

    printf("Enter the quantum: ");
    scanf("%d",&quantum);

    roundRobin(processes,n,quantum);
    printProcess(processes,n);
    return 0;
}
