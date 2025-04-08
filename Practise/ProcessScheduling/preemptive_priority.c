#include <stdio.h>

typedef struct {
    int pid, bt, priority, remaining_bt, wt, tat, at;
} Process;

void priorityScheduling(Process processes[], int n) {
    int completed = 0, time = 0, minPriority = 10000, minIndex = -1;
    int isCompleted[n];

    for (int i = 0; i < n; i++) {
        isCompleted[i] = 0; // Mark all processes as incomplete
        processes[i].remaining_bt = processes[i].bt;
    }

    while (completed < n) {
        minPriority = 10000, minIndex = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].at <= time && !isCompleted[i] && processes[i].priority < minPriority) {
                minPriority = processes[i].priority;
                minIndex = i;
            }
        }

        if (minIndex == -1) {
            time++;
            continue;
        }

        processes[minIndex].remaining_bt--;
        time++;

        if (processes[minIndex].remaining_bt == 0) {
            completed++;
            isCompleted[minIndex] = 1;
            processes[minIndex].tat = time - processes[minIndex].at;
            processes[minIndex].wt = processes[minIndex].tat - processes[minIndex].bt;
        }
    }
}

void printProcesses(Process processes[], int n) {
    printf("\nProcess\tPriority\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].priority, processes[i].at, processes[i].bt, processes[i].wt, processes[i].tat);
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time, burst time, and priority for process P%d: ", i + 1);
        scanf("%d %d %d", &processes[i].at, &processes[i].bt, &processes[i].priority);
    }

    priorityScheduling(processes, n);
    printProcesses(processes, n);

    return 0;
}
