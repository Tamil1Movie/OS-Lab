#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed.\n");
        return 1;
    } else if (pid == 0) {
        // Child process gets replaced by a new program
        execlp("/bin/echo", "echo", "Child process replaced by exec!", NULL);
    } else {
        // Parent process
        printf("Parent process: PID = %d\n", getpid());
    }
    return 0;
}

