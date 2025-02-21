#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"
#define OUTPUT_FILE "stats.txt"
#define MAX_SIZE 1024

int main() {
    char buffer[MAX_SIZE], result[MAX_SIZE];
    int fd, chars = 0, words = 1, lines = 1;

    fd = open(FIFO1, O_RDONLY);
    read(fd, buffer, sizeof(buffer));
    close(fd);

    for (int i = 0; buffer[i] != '\0'; i++) {
        chars++;
        if (buffer[i] == ' ')
            words++;
        if (buffer[i] == '\n')
            lines++;
    }

    snprintf(result, sizeof(result), "Characters: %d\nWords: %d\nLines: %d\n", chars, words, lines);

    fd = open(OUTPUT_FILE, O_WRONLY | O_CREAT, 0666);
    write(fd, result, strlen(result) + 1);
    close(fd);

    fd = open(FIFO2, O_WRONLY);
    write(fd, result, strlen(result) + 1);
    close(fd);

    return 0;
}

