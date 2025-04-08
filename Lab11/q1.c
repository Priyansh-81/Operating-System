#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void sstf(int req[], int n, int head) {
    int visited[100] = {0}, i, min, index, seek = 0, count = 0;
    while (count < n) {
        min = 9999;
        for (i = 0; i < n; i++) {
            if (!visited[i] && abs(head - req[i]) < min) {
                min = abs(head - req[i]);
                index = i;
            }
        }
        seek += abs(head - req[index]);
        head = req[index];
        visited[index] = 1;
        count++;
    }
    printf("Total Seek Time (SSTF): %d\n", seek);
}

void scan(int req[], int n, int head, int disk_size) {
    int seek = 0, i, j, temp;
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

    printf("Total Seek Time (SCAN): %d\n", seek);
}

void cscan(int req[], int n, int head, int disk_size) {
    int seek = 0, i, j, temp;
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
    seek += abs(disk_size - 1 - req[n - 1]);
    seek += abs(disk_size - 1 - req[0]);

    for (j = 0; j < i - 1; j++) seek += abs(req[j + 1] - req[j]);

    printf("Total Seek Time (C-SCAN): %d\n", seek);
}

void clook(int req[], int n, int head) {
    int seek = 0, i, j, temp;
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
    seek += abs(req[n - 1] - req[0]);
    for (j = 0; j < i - 1; j++) seek += abs(req[j + 1] - req[j]);

    printf("Total Seek Time (C-LOOK): %d\n", seek);
}

int main() {
    int req[100], n, head, disk_size, ch, i;
    printf("Enter number of requests: ");
    scanf("%d", &n);
    printf("Enter request queue: ");
    for (i = 0; i < n; i++) scanf("%d", &req[i]);
    printf("Enter initial head position: ");
    scanf("%d", &head);
    printf("Enter disk size: ");
    scanf("%d", &disk_size);

    do {
        printf("\nDisk Scheduling Menu (Lab)\n");
        printf("1. SSTF\n2. SCAN\n3. C-SCAN\n4. C-LOOK\n5. Exit\nEnter choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: sstf(req, n, head); break;
            case 2: scan(req, n, head, disk_size); break;
            case 3: cscan(req, n, head, disk_size); break;
            case 4: clook(req, n, head); break;
            case 5: break;
            default: printf("Invalid choice\n");
        }
    } while (ch != 5);
    return 0;
}