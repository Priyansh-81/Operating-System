#include <stdio.h>
#include <stdlib.h>

void fcfs(int req[], int n, int head) {
    int i, seek = 0;
    for (i = 0; i < n; i++) {
        seek += abs(req[i] - head);
        head = req[i];
    }
    printf("Total Seek Time (FCFS): %d\n", seek);
}

void look(int req[], int n, int head) {
    int i, j, temp, seek = 0;
    req[n] = head;
    n++;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (req[i] > req[j]) {
                temp = req[i];
                req[i] = req[j];
                req[j] = temp;
            }
        }
    }

    for (i = 0; i < n; i++) if (req[i] == head) break;

    for (j = i; j < n - 1; j++) seek += abs(req[j + 1] - req[j]);
    for (j = i; j > 0; j--) seek += abs(req[j] - req[j - 1]);

    printf("Total Seek Time (LOOK): %d\n", seek);
}

int main() {
    int req[100], n, head, ch, i;
    printf("Enter number of requests: ");
    scanf("%d", &n);
    printf("Enter request queue: ");
    for (i = 0; i < n; i++) scanf("%d", &req[i]);
    printf("Enter initial head position: ");
    scanf("%d", &head);

    do {
        printf("\nDisk Scheduling Menu (Additional)\n");
        printf("1. FCFS\n2. LOOK\n3. Exit\nEnter choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: fcfs(req, n, head); break;
            case 2: look(req, n, head); break;
            case 3: break;
            default: printf("Invalid choice\n");
        }
    } while (ch != 3);
    return 0;
}