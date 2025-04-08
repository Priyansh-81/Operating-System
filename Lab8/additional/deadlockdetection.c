#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int main() {
    int n, m;
    int Allocation[MAX_PROCESSES][MAX_RESOURCES];
    int Request[MAX_PROCESSES][MAX_RESOURCES];
    int Available[MAX_RESOURCES];
    int Finish[MAX_PROCESSES] = {0};  // 0 = false, 1 = true

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    printf("Enter Allocation Matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &Allocation[i][j]);

    printf("Enter Request Matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &Request[i][j]);

    printf("Enter Available Resources (%d):\n", m);
    for (int i = 0; i < m; i++)
        scanf("%d", &Available[i]);

    int count = 0;
    int progress = 1;

    while (progress) {
        progress = 0;

        for (int i = 0; i < n; i++) {
            if (Finish[i] == 0) {
                int canProceed = 1;

                for (int j = 0; j < m; j++) {
                    if (Request[i][j] > Available[j]) {
                        canProceed = 0;
                        break;
                    }
                }

                if (canProceed == 1) {
                    for (int j = 0; j < m; j++) {
                        Available[j] += Allocation[i][j];
                    }
                    Finish[i] = 1;
                    progress = 1;
                    count++;
                }
            }
        }
    }

    if (count == n)
        printf("\nNo Deadlock Detected. All processes can finish.\n");
    else {
        printf("\nDeadlock Detected. The following processes are in deadlock:\n");
        for (int i = 0; i < n; i++) {
            if (Finish[i] == 0)
                printf("Process %d\n", i);
        }
    }

    return 0;
}