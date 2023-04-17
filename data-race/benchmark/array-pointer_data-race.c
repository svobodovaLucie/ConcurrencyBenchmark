#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 10

void *thread_func(void *arg) {
    int *my_array = (int *)arg;
    int index = 0;
    while (index < 1) {
        my_array[index] = 1;
        index = 2;
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    int array[ARRAY_SIZE] = {0};

    pthread_create(&thread1, NULL, thread_func, array);
    pthread_create(&thread2, NULL, thread_func, array);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
