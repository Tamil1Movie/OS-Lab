#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define MAX_SIZE 1024
int main() {
    int pipe1[2], pipe2[2];
    pid_t pid;
    char filepath[MAX_SIZE], buffer[MAX_SIZE];

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("Pipe creation failed");
        exit(1);
    }
    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    if (pid > 0) { 
        close(pipe1[0]);  
        close(pipe2[1]);  
        printf("Enter the file path: ");
        scanf("%s", filepath);
        write(pipe1[1], filepath, strlen(filepath) + 1);
        close(pipe1[1]);  
        read(pipe2[0], buffer, sizeof(buffer));
        printf("File Contents:\n%s\n", buffer);
        close(pipe2[0]);

    } else { 
        close(pipe1[1]);  
        close(pipe2[0]);  
        read(pipe1[0], filepath, sizeof(filepath));
        close(pipe1[0]);  
        int fd = open(filepath, O_RDONLY);
        if (fd < 0) {
            perror("File opening failed");
            exit(1);
        }
        read(fd, buffer, sizeof(buffer));
        close(fd);
        write(pipe2[1], buffer, strlen(buffer) + 1);
        close(pipe2[1]);
    }

    return 0;
}
