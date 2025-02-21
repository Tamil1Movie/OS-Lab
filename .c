#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#define FIFO1 "/tmp/fifo1"
#define FIFO2 "/tmp/fifo2"
#define BUFFER_SIZE 1024

void create_fifo(const char *fifo_path) {
    if (mkfifo(fifo_path, 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }
}

int main() {
    char buffer[BUFFER_SIZE];
    int fd1, fd2;
    ssize_t bytes_read;

    create_fifo(FIFO1);
    create_fifo(FIFO2);

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        fd1 = open(FIFO1, O_WRONLY);
        if (fd1 == -1) {
            perror("open FIFO1");
            exit(EXIT_FAILURE);
        }

        printf("Enter a sentence: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        if (write(fd1, buffer, strlen(buffer) + 1) == -1) {
            perror("write to FIFO1");
            exit(EXIT_FAILURE);
        }
        close(fd1);

        fd2 = open(FIFO2, O_RDONLY);
        if (fd2 == -1) {
            perror("open FIFO2");
            exit(EXIT_FAILURE);
        }

        bytes_read = read(fd2, buffer, BUFFER_SIZE);
        if (bytes_read > 0) {
            printf("Statistics:\n%s\n", buffer);
        } else {
            perror("read from FIFO2");
        }
        close(fd2);

        wait(NULL);
    } else {
        fd1 = open(FIFO1, O_RDONLY);
        if (fd1 == -1) {
            perror("open FIFO1");
            exit(EXIT_FAILURE);
        }

        bytes_read = read(fd1, buffer, BUFFER_SIZE);
        close(fd1);

        if (bytes_read > 0) {
            int chars = 0, words = 0, lines = 0;
            int i = 0;
            int in_word = 0;

            while (buffer[i] != '\0') {
                chars++;
                if (buffer[i] == ' ' || buffer[i] == '\t') {
                    if (in_word) {
                        words++;
                        in_word = 0;
                    }
                } else if (buffer[i] == '\n') {
                    lines++;
                    if (in_word) {
                        words++;
                        in_word = 0;
                    }
                } else {
                    in_word = 1;
                }
                i++;
            }

            if (in_word) {
                words++;
            }

            char stats[BUFFER_SIZE];
            snprintf(stats, BUFFER_SIZE, "Characters: %d\nWords: %d\nLines: %d\n", chars, words, lines);

            fd2 = open(FIFO2, O_WRONLY);
            if (fd2 == -1) {
                perror("open FIFO2");
                exit(EXIT_FAILURE);
            }

            if (write(fd2, stats, strlen(stats) + 1) == -1) {
                perror("write to FIFO2");
                exit(EXIT_FAILURE);
            }
            close(fd2);
        }

        exit(EXIT_SUCCESS);
    }

    unlink(FIFO1);
    unlink(FIFO2);

    return 0;
}
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

