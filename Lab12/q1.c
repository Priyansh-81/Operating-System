#include <stdio.h>
#include <stdlib.h>

// Task structure
struct Task {
    int id;
    int execution_time;
    int period;
    int deadline;
};

// Compare function for Rate Monotonic (by period)
int compare_by_period(const void *a, const void *b) {
    return ((struct Task *)a)->period - ((struct Task *)b)->period;
}

// Compare function for EDF (by deadline)
int compare_by_deadline(const void *a, const void *b) {
    return ((struct Task *)a)->deadline - ((struct Task *)b)->deadline;
}

// Rate Monotonic Scheduling
void rate_monotonic(struct Task tasks[], int n) {
    int hyper_period = 1;
    for (int i = 0; i < n; i++)
        hyper_period *= tasks[i].period; // LCM can be used for better accuracy

    qsort(tasks, n, sizeof(struct Task), compare_by_period);

    printf("\n[Rate Monotonic Schedule for %d units]:\n", hyper_period);
    for (int time = 0; time < hyper_period; time++) {
        int executed = 0;
        for (int i = 0; i < n; i++) {
            if (time % tasks[i].period == 0) {
                tasks[i].deadline = time + tasks[i].period; // Reset deadline
            }
        }
        for (int i = 0; i < n; i++) {
            if (time < tasks[i].deadline && tasks[i].execution_time > 0) {
                printf("Time %d: Task %d\n", time, tasks[i].id);
                tasks[i].execution_time--;
                executed = 1;
                break;
            }
        }
        if (!executed)
            printf("Time %d: Idle\n", time);
    }
}

// Earliest Deadline First Scheduling
void earliest_deadline_first(struct Task tasks[], int n) {
    int hyper_period = 1;
    for (int i = 0; i < n; i++)
        hyper_period *= tasks[i].period;

    printf("\n[Earliest Deadline First Schedule for %d units]:\n", hyper_period);

    int time = 0;
    while (time < hyper_period) {
        for (int i = 0; i < n; i++) {
            if (time % tasks[i].period == 0) {
                tasks[i].execution_time = tasks[i].period / 2;
                tasks[i].deadline = time + tasks[i].period;
            }
        }

        qsort(tasks, n, sizeof(struct Task), compare_by_deadline);

        int executed = 0;
        for (int i = 0; i < n; i++) {
            if (tasks[i].execution_time > 0 && time < tasks[i].deadline) {
                printf("Time %d: Task %d\n", time, tasks[i].id);
                tasks[i].execution_time--;
                executed = 1;
                break;
            }
        }

        if (!executed)
            printf("Time %d: Idle\n", time);

        time++;
    }
}

int main() {
    int n, choice;
    printf("Enter number of tasks: ");
    scanf("%d", &n);

    struct Task *tasks = (struct Task *)malloc(n * sizeof(struct Task));
    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        printf("Enter execution time for Task %d: ", i + 1);
        scanf("%d", &tasks[i].execution_time);
        printf("Enter period for Task %d: ", i + 1);
        scanf("%d", &tasks[i].period);
        tasks[i].deadline = tasks[i].period;
    }

    do {
        printf("\nMenu:\n1. Rate Monotonic Scheduling\n2. Earliest Deadline First\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        if (choice == 1) {
            rate_monotonic(tasks, n);
        } else if (choice == 2) {
            earliest_deadline_first(tasks, n);
        }
    } while (choice != 3);

    free(tasks);
    return 0;
}