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

    printf("Producer: Enter 5 numbers: ");
    for (int i = 0; i < 5; i++) {
        scanf("%d", &data[i]);
    }
    data[5] = -1;  // End marker

    shmdt(data);
    return 0;
}

