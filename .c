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