#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();  // Create child process

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child Process:\n");
        printf("PID: %d, PPID: %d\n", getpid(), getppid());
    } else {
        // Parent process
        printf("Parent Process:\n");
        printf("PID: %d, Child PID: %d\n", getpid(), pid);
    }

    return 0;
}
