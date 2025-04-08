#include<stdio.h>

typedef struct{
    int pid,bt,wt,tat,ct;
}process;

float avgwt(process processes[], int n){
    float sum_wt=0.0;
    for(int i=0;i<n;i++){
        sum_wt+=processes[i].wt;
    }
    return sum_wt/n;
}

float avgtat(process processes[], int n){
    float sum_tat=0.0;
    for(int i=0;i<n;i++){
        sum_tat+=processes[i].tat;
    }
    return sum_tat/n;
}

void fcfs(process processes[], int n){
    processes[0].wt=0;
    for(int i=1;i<n;i++){
        processes[i].wt=processes[i-1].wt+processes[i-1].bt;
    }
    for(int i=0;i<n;i++){
        processes[i].tat=processes[i].bt+processes[i].wt;
    }
    for(int i=0;i<n;i++){
        processes[i].ct=processes[i].wt+processes[i].bt;
    }
}

void printDetails(process processes[],int n){
    printf("PID\tBT\tWT\tTAT\tCT\n");
    for(int i =0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\n",processes[i].pid,processes[i].bt,processes[i].wt,processes[i].tat,processes[i].ct);
    }
    printf("\nAverage Wait time: %.2f\nAverage Turn Around Time: %.2f\n",avgwt(processes,n),avgtat(processes,n));
}

void main(){
    printf("Enter the number of processes: ");
    int n;
    scanf("%d",&n);
    process processes[n];
    for(int i=0;i<n;i++){
        processes[i].pid=i+1;
    }
    printf("Enter the burst time for the processes: \n");
    for(int i=0;i<n;i++){
        printf("Enter CPU burst time for process %d: ",processes[i].pid);
        scanf("%d",&processes[i].bt);
    }
    fcfs(processes,n);
    printDetails(processes,n);
}