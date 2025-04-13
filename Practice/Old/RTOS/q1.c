#include <stdio.h>
#include <stdbool.h>

#define MAX_TASKS 10

// Structure to represent a task
typedef struct {
    int id;               // Task ID
    int period;           // Period (for RM scheduling)
    int execution_time;   // Execution time (CPU burst)
    int deadline;         // Absolute deadline (for EDF scheduling)
    int remaining_time;   // Remaining execution time
    int next_deadline;    // Next deadline instance
} Task;

// Function to simulate Rate-Monotonic Scheduling
void rate_monotonic(Task tasks[], int n, int time_frame) {
    printf("\nRate-Monotonic Scheduling:\n");

    for (int time = 0; time < time_frame; time++) {
        int min_period = __INT_MAX__;
        int selected_task = -1;

        // Select task with the shortest period (highest priority)
        for (int i = 0; i < n; i++) {
            if (time % tasks[i].period == 0) {
                tasks[i].remaining_time = tasks[i].execution_time; // Reset task
            }

            if (tasks[i].remaining_time > 0 && tasks[i].period < min_period) {
                min_period = tasks[i].period;
                selected_task = i;
            }
        }

        if (selected_task != -1) {
            printf("Time %d: Task %d executing\n", time, tasks[selected_task].id);
            tasks[selected_task].remaining_time--;
        } else {
            printf("Time %d: Idle\n", time);
        }
    }
}

// Function to simulate Earliest-Deadline-First Scheduling
void earliest_deadline_first(Task tasks[], int n, int time_frame) {
    printf("\nEarliest-Deadline-First Scheduling:\n");

    for (int time = 0; time < time_frame; time++) {
        int min_deadline = __INT_MAX__;
        int selected_task = -1;

        // Update deadlines and reset execution if period is reached
        for (int i = 0; i < n; i++) {
            if (time % tasks[i].period == 0) {
                tasks[i].remaining_time = tasks[i].execution_time;
                tasks[i].next_deadline = time + tasks[i].deadline;
            }

            if (tasks[i].remaining_time > 0 && tasks[i].next_deadline < min_deadline) {
                min_deadline = tasks[i].next_deadline;
                selected_task = i;
            }
        }

        if (selected_task != -1) {
            printf("Time %d: Task %d executing\n", time, tasks[selected_task].id);
            tasks[selected_task].remaining_time--;
        } else {
            printf("Time %d: Idle\n", time);
        }
    }
}

int main() {
    int n, time_frame;
    Task tasks[MAX_TASKS];

    // Input task details
    printf("Enter number of tasks: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter period, execution time, and deadline for Task %d: ", i + 1);
        scanf("%d %d %d", &tasks[i].period, &tasks[i].execution_time, &tasks[i].deadline);
        tasks[i].id = i + 1;
        tasks[i].remaining_time = 0;
        tasks[i].next_deadline = tasks[i].deadline;
    }

    printf("Enter time frame for simulation: ");
    scanf("%d", &time_frame);

    // Run RM and EDF scheduling
    rate_monotonic(tasks, n, time_frame);
    earliest_deadline_first(tasks, n, time_frame);

    return 0;
}
