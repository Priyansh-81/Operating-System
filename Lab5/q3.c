#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX 100  // Max number of strings
#define LEN 100  // Max length of each string

// Bubble Sort function
void bubbleSort(char arr[][LEN], int n) {
    char temp[LEN];
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(arr[j], arr[j + 1]) > 0) {
                strcpy(temp, arr[j]);
                strcpy(arr[j], arr[j + 1]);
                strcpy(arr[j + 1], temp);
            }
        }
    }
}

// Selection Sort function
void selectionSort(char arr[][LEN], int n) {
    char temp[LEN];
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (strcmp(arr[j], arr[minIndex]) < 0) {
                minIndex = j;
            }
        }
        strcpy(temp, arr[i]);
        strcpy(arr[i], arr[minIndex]);
        strcpy(arr[minIndex], temp);
    }
}

int main() {
    int n;
    printf("Enter number of strings: ");
    scanf("%d", &n);

    char strings[MAX][LEN];

    // Read strings
    printf("Enter %d strings:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%s", strings[i]);
    }

    pid_t pid1, pid2;

    // Create first child process (Bubble Sort)
    pid1 = fork();

    if (pid1 == 0) {
        printf("\nChild 1 (Bubble Sort) Process ID: %d\n", getpid());
        bubbleSort(strings, n);
        printf("Sorted Strings (Bubble Sort):\n");
        for (int i = 0; i < n; i++) {
            printf("%s\n", strings[i]);
        }
        exit(0);
    }

    // Create second child process (Selection Sort)
    pid2 = fork();

    if (pid2 == 0) {
        printf("\nChild 2 (Selection Sort) Process ID: %d\n", getpid());
        selectionSort(strings, n);
        printf("Sorted Strings (Selection Sort):\n");
        for (int i = 0; i < n; i++) {
            printf("%s\n", strings[i]);
        }
        exit(0);
    }

    // Parent process waits for any one child to finish
    int status;
    pid_t completedChild = wait(&status);
    printf("\nParent Process: One child (%d) has completed.\n", completedChild);

    return 0;
}
