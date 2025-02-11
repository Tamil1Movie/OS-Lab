#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {
        printf("Child Process: My PID is %d\n", getpid());
    } else {
        printf("Parent Process: My child's PID is %d\n", pid);
        wait(NULL);
    }

    return 0;
}
