#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed.\n");
        return 1;
    } else if (pid == 0) {
        printf("Child process: PID = %d\n", getpid());
        sleep(2); // Simulate child execution time
        printf("Child process exiting.\n");
    } else {
        printf("Parent process waiting for child to exit.\n");
        wait(NULL);  // Wait for child to exit
        printf("Parent process: Child has exited.\n");
    }
    return 0;
}

