#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void sstf(int request[], int n, int head) {
    int totalSeek = 0, completed[MAX] = {0}, current = head;
    printf("SSTF Order: %d", head);

    for (int i = 0; i < n; i++) {
        int minDist = 999999, index = -1; // Replaced INT_MAX with a large number
        for (int j = 0; j < n; j++) {
            if (!completed[j] && abs(request[j] - current) < minDist) {
                minDist = abs(request[j] - current);
                index = j;
            }
        }
        if (index != -1) {
            completed[index] = 1;
            totalSeek += minDist;
            current = request[index];
            printf(" -> %d", current);
        }
    }
    printf("\nTotal Seek Time: %d\n", totalSeek);
}

void scan(int request[], int n, int head, int max, int direction) {
    int totalSeek = 0;
    printf("SCAN Order: %d", head);

    int left[MAX], right[MAX];
    int l = 0, r = 0;

    for (int i = 0; i < n; i++) {
        if (request[i] < head) left[l++] = request[i];
        else right[r++] = request[i];
    }

    if (direction == 0) {
        for (int i = l - 1; i >= 0; i--) {
            totalSeek += abs(head - left[i]);
            head = left[i];
            printf(" -> %d", head);
        }
        totalSeek += head; // Move to 0
        head = 0;
        for (int i = 0; i < r; i++) {
            totalSeek += abs(head - right[i]);
            head = right[i];
            printf(" -> %d", head);
        }
    } else {
        for (int i = 0; i < r; i++) {
            totalSeek += abs(head - right[i]);
            head = right[i];
            printf(" -> %d", head);
        }
        totalSeek += (max - head); // Move to max
        head = max;
        for (int i = l - 1; i >= 0; i--) {
            totalSeek += abs(head - left[i]);
            head = left[i];
            printf(" -> %d", head);
        }
    }
    printf("\nTotal Seek Time: %d\n", totalSeek);
}

void cscan(int request[], int n, int head, int max) {
    int totalSeek = 0;
    printf("C-SCAN Order: %d", head);

    int right[MAX], left[MAX];
    int r = 0, l = 0;

    for (int i = 0; i < n; i++) {
        if (request[i] >= head) right[r++] = request[i];
        else left[l++] = request[i];
    }

    for (int i = 0; i < r; i++) {
        totalSeek += abs(head - right[i]);
        head = right[i];
        printf(" -> %d", head);
    }

    totalSeek += (max - head); // Move to max
    totalSeek += max;          // Wrap around to 0
    head = 0;

    for (int i = 0; i < l; i++) {
        totalSeek += abs(head - left[i]);
        head = left[i];
        printf(" -> %d", head);
    }

    printf("\nTotal Seek Time: %d\n", totalSeek);
}

void clook(int request[], int n, int head) {
    int totalSeek = 0;
    printf("C-LOOK Order: %d", head);

    int right[MAX], left[MAX];
    int r = 0, l = 0;

    for (int i = 0; i < n; i++) {
        if (request[i] >= head) right[r++] = request[i];
        else left[l++] = request[i];
    }

    for (int i = 0; i < r; i++) {
        totalSeek += abs(head - right[i]);
        head = right[i];
        printf(" -> %d", head);
    }

    for (int i = 0; i < l; i++) {
        totalSeek += abs(head - left[i]);
        head = left[i];
        printf(" -> %d", head);
    }

    printf("\nTotal Seek Time: %d\n", totalSeek);
}

int main() {
    int n, head, choice, direction, max;
    int request[MAX];

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter the requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &request[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter maximum cylinder value: ");
    scanf("%d", &max);

    do {
        printf("\nDisk Scheduling Algorithms:\n");
        printf("1. SSTF\n2. SCAN\n3. C-SCAN\n4. C-LOOK\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                sstf(request, n, head);
                break;
            case 2:
                printf("Enter direction (0 for left, 1 for right): ");
                scanf("%d", &direction);
                scan(request, n, head, max, direction);
                break;
            case 3:
                cscan(request, n, head, max);
                break;
            case 4:
                clook(request, n, head);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}
