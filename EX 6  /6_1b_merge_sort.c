
#include <stdio.h>
#include <pthread.h>

#define MAX_SIZE 100

int arr[MAX_SIZE], size;

void merge(int left, int mid, int right) {
    int i = left, j = mid + 1, k = 0;
    int temp[right - left + 1];

    while (i <= mid && j <= right)
        temp[k++] = (arr[i] < arr[j]) ? arr[i++] : arr[j++];

    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    for (i = left, k = 0; i <= right; i++, k++) arr[i] = temp[k];
}

void* merge_sort(void* arg) {
    int* bounds = (int*)arg;
    int left = bounds[0], right = bounds[1];

    if (left < right) {
        int mid = (left + right) / 2;
        int left_part[] = {left, mid}, right_part[] = {mid + 1, right};

        pthread_t t1, t2;
        pthread_create(&t1, NULL, merge_sort, left_part);
        pthread_create(&t2, NULL, merge_sort, right_part);

        pthread_join(t1, NULL);
        pthread_join(t2, NULL);
        merge(left, mid, right);
    }

    pthread_exit(NULL);
}

int main() {
    printf("Enter number of elements: ");
    scanf("%d", &size);

    printf("Enter %d elements: ", size);
    for (int i = 0; i < size; i++) scanf("%d", &arr[i]);

    pthread_t t;
    int bounds[] = {0, size - 1};
    pthread_create(&t, NULL, merge_sort, bounds);
    pthread_join(t, NULL);

    printf("Sorted Array: ");
    for (int i = 0; i < size; i++) printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
