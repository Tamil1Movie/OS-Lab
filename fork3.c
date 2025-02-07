#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int global_var = 10;

int main() {
    pid_t pid;
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {
        global_var -= 5;
        printf("Child Process: Global variable value = %d\n", global_var);
    } else {
        wait(NULL);
        global_var += 5;
        printf("Parent Process: Global variable value = %d\n", global_var);
    }

    return 0;
}
