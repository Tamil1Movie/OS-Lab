#include <stdio.h>
#include <pthread.h>

#define MAX_SIZE 100

int arr[MAX_SIZE], even[MAX_SIZE], odd[MAX_SIZE];
int size, evenCount = 0, oddCount = 0;
double evenAvg = 0, oddAvg = 0;

void* sort_even(void* arg) {
    for (int i = 0; i < evenCount - 1; i++) {
        for (int j = 0; j < evenCount - i - 1; j++) {
            if (even[j] > even[j + 1]) {
                int temp = even[j];
                even[j] = even[j + 1];
                even[j + 1] = temp;
            }
        }
    }
    pthread_exit(NULL);
}

void* sort_odd(void* arg) {
    for (int i = 0; i < oddCount - 1; i++) {
        for (int j = 0; j < oddCount - i - 1; j++) {
            if (odd[j] > odd[j + 1]) {
                int temp = odd[j];
                odd[j] = odd[j + 1];
                odd[j + 1] = temp;
            }
        }
    }
    pthread_exit(NULL);
}

void* compute_average(void* arg) {
    int sumEven = 0, sumOdd = 0;
    for (int i = 0; i < evenCount; i++) sumEven += even[i];
    for (int i = 0; i < oddCount; i++) sumOdd += odd[i];
    evenAvg = (evenCount > 0) ? (double)sumEven / evenCount : 0;
    oddAvg = (oddCount > 0) ? (double)sumOdd / oddCount : 0;
    pthread_exit(NULL);
}

int main() {
    printf("Enter number of elements: ");
    scanf("%d", &size);

    printf("Enter %d elements: ", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
        if (arr[i] % 2 == 0) even[evenCount++] = arr[i];
        else odd[oddCount++] = arr[i];
    }

    pthread_t t1, t2, t3;
    pthread_create(&t1, NULL, sort_even, NULL);
    pthread_create(&t2, NULL, sort_odd, NULL);
    pthread_create(&t3, NULL, compute_average, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("Sorted Even: ");
    for (int i = 0; i < evenCount; i++) printf("%d ", even[i]);
    printf("\nSorted Odd: ");
    for (int i = 0; i < oddCount; i++) printf("%d ", odd[i]);
    printf("\nEven Avg: %.2f, Odd Avg: %.2f\n", evenAvg, oddAvg);

    return 0;
}
