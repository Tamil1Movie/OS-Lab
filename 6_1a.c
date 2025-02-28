#include <stdio.h>
#include <pthread.h>

#define SIZE 2  // Matrix size

int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];

typedef struct {
    int row, col;
} ThreadData;

void* multiply(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int sum = 0;
    for (int i = 0; i < SIZE; i++) {
        sum += A[data->row][i] * B[i][data->col];
    }
    C[data->row][data->col] = sum;
    pthread_exit(NULL);
}

int main() {
    printf("Enter elements of first matrix (%d x %d):\n", SIZE, SIZE);
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            scanf("%d", &A[i][j]);

    printf("Enter elements of second matrix (%d x %d):\n", SIZE, SIZE);
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            scanf("%d", &B[i][j]);

    pthread_t threads[SIZE][SIZE];
    ThreadData threadData[SIZE][SIZE];

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            threadData[i][j].row = i;
            threadData[i][j].col = j;
            pthread_create(&threads[i][j], NULL, multiply, &threadData[i][j]);
        }
    }

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            pthread_join(threads[i][j], NULL);

    printf("Resultant Matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }

    return 0;
}

