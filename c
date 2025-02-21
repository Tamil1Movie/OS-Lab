Here are sample C programs for each of the specified tasks related to fork, exec, and wait system calls.
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 1024

int main() {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    int *data = (int *)shmat(shmid, (void *)0, 0);

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid > 0) { // Producer process
        printf("Producer: Enter 5 numbers: ");
        for (int i = 0; i < 5; i++) {
            scanf("%d", &data[i]);
        }
        data[5] = -1; // End marker

        wait(NULL); // Wait for child (consumer) to finish

        // Detach and remove shared memory
        shmdt(data);
        shmctl(shmid, IPC_RMID, NULL);
    } 
    else { // Consumer process
        sleep(1); // Give some time for producer to write

        int sum = 0, i = 0;
        printf("Consumer: Received numbers: ");
        while (data[i] != -1) {
            printf("%d ", data[i]);
            sum += data[i++];
        }
        printf("\nSum = %d\n", sum);

        shmdt(data);
    }

    return 0;
}
1. Simulate fork system call for given conditions

(a) Compute fork invocations and message prints

#include <stdio.h>
#include <unistd.h>

int main() {
    int i;
    for (i = 0; i < 4; i++) {
        fork();  // Invoke fork 4 times
    }
    printf("Welcome to OS Lab\n");
    return 0;
}

Analysis:
The total number of processes after 4 forks is ￼. Therefore, “Welcome to OS Lab” will be printed 16 times.

(b) Distinguish parent and child processes and print PIDs

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed.\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child Process: PID = %d\n", getpid());
    } else {
        // Parent process
        printf("Parent Process: Child PID = %d\n", pid);
    }
    return 0;
}

(c) Global variable manipulation in parent and child processes

#include <stdio.h>
#include <unistd.h>

int global_var = 10;

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed.\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        global_var -= 5;
        printf("Child Process: Global variable = %d\n", global_var);
    } else {
        // Parent process
        global_var += 5;
        printf("Parent Process: Global variable = %d\n", global_var);
    }
    return 0;
}

2. Simulate exec system call to replace child process

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

3. Execute ls command using exec in the child process

#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed.\n");
        return 1;
    } else if (pid == 0) {
        // Replace child process with ls command
        execlp("/bin/ls", "ls", NULL);
    } else {
        printf("Parent process: Waiting for child to complete ls command.\n");
    }
    return 0;
}

4. Simulate wait system call

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

Let me know if you need detailed explanations for any specific part of the code.