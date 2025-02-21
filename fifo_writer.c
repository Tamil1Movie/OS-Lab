
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"
#define MAX_SIZE 1024

int main() {
    char sentence[MAX_SIZE], buffer[MAX_SIZE];
    int fd;

    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    printf("Enter a sentence: ");
    fgets(sentence, MAX_SIZE, stdin);

    fd = open(FIFO1, O_WRONLY);
    write(fd, sentence, strlen(sentence) + 1);
    close(fd);

    fd = open(FIFO2, O_RDONLY);
    read(fd, buffer, sizeof(buffer));
    printf("Statistics:\n%s\n", buffer);
    close(fd);

    unlink(FIFO1);
    unlink(FIFO2);

    return 0;
}
