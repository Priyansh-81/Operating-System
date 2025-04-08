#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

// Function to swap two strings
void swap(char **a, char **b) {
    char *temp = *a;
    *a = *b;
    *b = temp;
}

// Function to sort strings using Bubble Sort
void sortStrings(char *arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(arr[j], arr[j + 1]) > 0) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <string1> <string2> ... <stringN>\n", argv[0]);
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process: Sort and display strings
        printf("\nChild Process (Sorted Strings):\n");
        sortStrings(argv + 1, argc - 1);  // Sort arguments (excluding program name)
        for (int i = 1; i < argc; i++) {
            printf("%s\n", argv[i]);
        }
        printf("\n");
    } else {
        // Parent process: Wait for child to finish
        wait(NULL);
        printf("Parent Process (Unsorted Strings):\n");
        for (int i = 1; i < argc; i++) {
            printf("%s\n", argv[i]);
        }
        printf("\n");
    }

    return 0;
}
