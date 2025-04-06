#include <stdio.h>

typedef struct {
    int pid, bt, at, remaining_bt, wt, tat;
} Process;

void roundRobin(Process processes[], int n, int quantum) {
    int time = 0, completed = 0;
    int isCompleted[n];

    for (int i = 0; i < n; i++) {
        processes[i].remaining_bt = processes[i].bt;
        isCompleted[i] = 0;
    }

    while (completed < n) {
        int allIdle = 1;

        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_bt > 0) {
                allIdle = 0;

                if (processes[i].remaining_bt > quantum) {
                    time += quantum;
                    processes[i].remaining_bt -= quantum;
                } else {
                    time += processes[i].remaining_bt;
                    processes[i].tat = time - processes[i].at;
                    processes[i].wt = processes[i].tat - processes[i].bt;
                    processes[i].remaining_bt = 0;
                    completed++;
                }
            }
        }

        if (allIdle) break;
    }
}

void printProcesses(Process processes[], int n) {
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].at, processes[i].bt, processes[i].wt, processes[i].tat);
    }
}

int main() {
    int n, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time and burst time for process P%d: ", i + 1);
        scanf("%d %d", &processes[i].at, &processes[i].bt);
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    roundRobin(processes, n, quantum);
    printProcesses(processes, n);

    return 0;
}
