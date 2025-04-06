#include<stdio.h>

typedef struct process{
    int pid,at,bt,rem_bt,wt,tat;
}process;

void shortest_prem(process processes[],int n){
    int completed=0, time=0, minIndex=-1, minBurst=10000;
    int isCompleted[n];
    for(int i=0;i<n;i++){
        isCompleted[i]=0;
        processes[i].rem_bt=processes[i].bt;
    }
    while(completed<n){
        minBurst=10000;
        minIndex=-1;

        for(int i=0;i<n;i++){
            if(processes[i].at<time && !isCompleted[i] && processes[i].rem_bt<minBurst){
                minBurst=processes[i].rem_bt;
                minIndex=i;
            }
        }
        if(minIndex == -1){
            time++;
            continue;
        }
        processes[minIndex].rem_bt--;
        time++;

        if (processes[minIndex].rem_bt == 0) {
            completed++;
            isCompleted[minIndex] = 1;
            processes[minIndex].tat = time - processes[minIndex].at;
            processes[minIndex].wt = processes[minIndex].tat - processes[minIndex].bt;
        }
    }
}

void printProcesses(process processes[], int n) {
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].at, processes[i].bt, processes[i].wt, processes[i].tat);
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time and burst time for process P%d: ", i + 1);
        scanf("%d %d", &processes[i].at, &processes[i].bt);
    }

    shortest_prem(processes, n);
    printProcesses(processes, n);

    return 0;
}
