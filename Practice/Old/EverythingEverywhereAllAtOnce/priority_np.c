#include<stdio.h>

typedef struct{
    int pid,priority,bt,wt,tat;
}process;

float avg_wt(process processes[], int n){
    float s=0.0;
    for(int i=0;i<n;i++){
        s+=processes[i].wt;
    }
    return s/n;
}

float avg_tat(process processes[], int n){
    float s=0.0;
    for(int i=0;i<n;i++){
        s+=processes[i].tat;
    }
    return s/n;
}

void priority(process processes[], int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if(processes[j].priority>processes[j+1].priority){
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

void printDetails(process processes[], int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if(processes[j].pid>processes[j+1].pid){
                process temp=processes[j];
                processes[j]=processes[j+1];
                processes[j+1]=temp;
            }
        }
    }
    printf("PID\tPriority\tBT\tWT\tTAT\n");
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\n",processes[i].pid,processes[i].priority,processes[i].bt,processes[i].wt,processes[i].tat);
    }
    printf("\nAverage Wait Time: %.2f\nAverage Turn Around Time: %.2f\n",avg_wt(processes,n),avg_tat(processes,n));

    printf("\nGantt Chart:\n");

    // Top bar
    printf(" ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < processes[i].bt; j++) printf("--");
        printf(" ");
    }
    printf("\n|");

    // Process names in the middle
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < processes[i].bt - 1; j++) printf(" ");
        printf("P%d", processes[i].pid);
        for (int j = 0; j < processes[i].bt - 1; j++) printf(" ");
        printf("|");
    }

    // Bottom bar
    printf("\n ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < processes[i].bt; j++) printf("--");
        printf(" ");
    }

    // Timeline
    printf("\n0");
    int time = 0;
    for (int i = 0; i < n; i++) {
        time += processes[i].bt;
        printf("%*d", processes[i].bt * 2, time);
    }
    printf("\n");
}

int main(){
    int n;
    printf("Enter the number of processes: ");
    scanf("%d",&n);
    process processes[n];
    for(int i=0;i<n;i++){
        processes[i].pid=i+1;
    }
    printf("Enter the CPU cycles and priority for each process->\n");
    for(int i=0;i<n;i++){
        printf("Process %d: ",processes[i].pid);
        scanf("%d%d",&processes[i].bt,&processes[i].priority);
    }
    priority(processes,n);
    printDetails(processes,n);
    return 0;
}