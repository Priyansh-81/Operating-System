#include<stdio.h>

typedef struct {
    int pid, bt, wt, tat, ct;
}process;

float calcavgwt(process processes[], int n){
    float avgwt=0;
    for(int i=0;i<n;i++){
        avgwt+=processes[i].wt;
    }
    return avgwt/n;
}

float calcavgtat(process processes[], int n){
    float avgtat=0;
    for(int i=0;i<n;i++){
        avgtat+=processes[i].tat;
    }
    return avgtat/n;
}

void fcfs(process processes[], int n){
    for(int i=0;i<n;i++){
        processes[i].pid=i+1;
    }
    processes[0].wt=0;
    for(int i=1;i<n;i++)
        processes[i].wt=processes[i-1].wt+processes[i-1].bt;
    for(int i=0;i<n;i++){
        processes[i].tat=processes[i].bt+processes[i].wt;
    }
}

void displayProcesses(process processes[], int n){
    printf("PID\tBT\tWT\tTAT\n");
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\n",processes[i].pid,processes[i].bt, processes[i].wt, processes[i].tat);
    }
    printf("The Average wait time is %.2f and the Average turn around time is %.2f\n", calcavgwt(processes,n), calcavgtat(processes, n));
}

int main(){
    printf("Enter the number of processes:\t");
    int n;
    scanf("%d",&n);
    process processes[n];
    printf("Enter the burst time for the processes\n");
    for(int i=0;i<n;i++){
        printf("Process %d: ",i+1);
        scanf("%d",&processes[i].bt);
    }
    fcfs(processes,n);
    displayProcesses(processes, n);
    return 0;
}
