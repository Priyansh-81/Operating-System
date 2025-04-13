#include<stdio.h>

typedef struct process{
    int pid,bt,wt,tat;
}process;

void timecalc(process processes[],int n){
    processes[0].wt=0;

    for(int i=1;i<n;i++){
        processes[i].wt=processes[i-1].wt+processes[i-1].bt;
    }

    for(int i=0; i<n; i++){
        processes[i].tat = processes[i].bt + processes[i].wt;
    }
}

float average_wt(process processes[], int n){
    float sum=0;
    for(int i=0;i<n;i++){
        sum+=processes[i].wt;
    }
    return sum/n;
}

float average_tat(process processes[], int n){
    float sum=0;
    for(int i=0;i<n;i++){
        sum+=processes[i].tat;
    }
    return sum/n;
}

int main(){
    printf("Enter the number of processes: ");
    int n;
    scanf("%d",&n);
    process processes[n];

    for(int i=0;i<n;i++){
        processes[i].pid=i+1;
    }
    printf("Enter the burst time for the processes\n");
    for(int i=0;i<n;i++){
        printf("Process %d: ",processes[i].pid);
        scanf("%d",&processes[i].bt);
    }

    timecalc(processes,n);
    printf("The wait time and turn around time of all the processes is: \n");
    for(int i=0;i<n;i++){
        printf("Process %d:\t%d\t%d\n",processes[i].pid,processes[i].wt,processes[i].tat);
    }
    printf("\nThe average wait time is %.2f and the average turn around time is %.2f\n",average_wt(processes, n),average_tat(processes,n));
    return 0;
}
