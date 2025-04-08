#include<stdio.h>
//assumption every single process arive at the same time

typedef struct{
    int pid,bt,wt,tat;
}process;

float avg_wt(process processes[],int n){
    float sum_wt=0.0;
    for(int i=0;i<n;i++){
        sum_wt+=processes[i].wt;
    }
    return sum_wt/n;
}

float avg_tat(process processes[],int n){
    float sum_tat=0.0;
    for(int i=0;i<n;i++){
        sum_tat+=processes[i].tat;
    }
    return sum_tat/n;
}

void sjf(process processes[],int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if(processes[j].bt>processes[j+1].bt){
                process temp=processes[j];
                processes[j]=processes[j+1];
                processes[j+1]=temp;
            }
        }
    }

    processes[0].wt=0;
    for(int i=1;i<n;i++){
        processes[i].wt=processes[i-1].wt+processes[i-1].bt;
    }
    for(int i=0;i<n;i++){
        processes[i].tat=processes[i].wt+processes[i].bt;
    }
}

void printThing(process processes[], int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if(processes[j].pid>processes[j+1].pid){
                process temp=processes[j];
                processes[j]=processes[j+1];
                processes[j+1]=temp;
            }
        }
    }
    printf("PID\tBT\tWT\tTAT\n");
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\n",processes[i].pid,processes[i].bt,processes[i].wt,processes[i].tat);
    }
    printf("\nAverage Wait time: %.2f\nAverage Turn Around Time: %.2f\n",avg_wt(processes,n),avg_tat(processes,n));
}

int main(){
    int n;
    printf("Enter the number of processes: ");
    scanf("%d",&n);
    process processes[n];
    for(int i=0;i<n;i++){
        processes[i].pid=i+1;
    }
    printf("Enter the burst time for the processes->\n");
    for(int i=0;i<n;i++){
        printf("Enter the CPU burst time for process %d :",processes[i].pid);
        scanf("%d",&processes[i].bt);
    }
    sjf(processes,n);
    printThing(processes,n);
    return 0;
}