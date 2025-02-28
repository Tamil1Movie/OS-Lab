#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main() {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, SHM_SIZE, 0666);
    int *data = (int *)shmat(shmid, (void *)0, 0);

    int sum = 0, i = 0;
    printf("Consumer: Received numbers: ");
    while (data[i] != -1) {
        printf("%d ", data[i]);
        sum += data[i++];
    }
    printf("\nSum = %d\n", sum);

    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}

