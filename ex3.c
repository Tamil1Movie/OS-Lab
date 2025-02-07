#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed.\n");
        return 1;
    } else if (pid == 0) {
        execlp("/bin/ls", "ls", NULL);
    } else {
        printf("Parent process: Waiting for child to complete ls command.\n");
    }
    return 0;
}

