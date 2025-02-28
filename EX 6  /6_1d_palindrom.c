#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define MAX_SIZE 100

char words[MAX_SIZE][100];
int results[MAX_SIZE], size;

void* check_palindrome(void* arg) {
    int index = *(int*)arg;
    char* str = words[index];
    int len = strlen(str), isPalindrome = 1;

    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - i - 1]) {
            isPalindrome = 0;
            break;
        }
    }

    results[index] = isPalindrome;
    pthread_exit(NULL);
}

int main() {
    printf("Enter number of strings: ");
    scanf("%d", &size);

    printf("Enter %d strings:\n", size);
    for (int i = 0; i < size; i++) scanf("%s", words[i]);

    pthread_t threads[MAX_SIZE];
    int indices[MAX_SIZE];

    for (int i = 0; i < size; i++) {
        indices[i] = i;
        pthread_create(&threads[i], NULL, check_palindrome, &indices[i]);
    }

    for (int i = 0; i < size; i++) {
        pthread_join(threads[i], NULL);
        printf("\"%s\" is %s palindrome\n", words[i], results[i] ? "a" : "not a");
    }

    return 0;
}
