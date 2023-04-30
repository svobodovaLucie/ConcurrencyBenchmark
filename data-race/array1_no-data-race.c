#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 10

int my_array[ARRAY_SIZE];

void *thread_func(void *arg) {
    int index = *((int *)arg);
    my_array[index] += 1;           // no data race
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    int arg1 = 0;

    pthread_create(&thread1, NULL, thread_func, &arg1);

    pthread_join(thread1, NULL);

    printf("Final array:\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", my_array[i]); // no data race - threads are joined
    }
    printf("\n");

    return 0;
}
