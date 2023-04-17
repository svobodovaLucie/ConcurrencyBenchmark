/*
The increment_count function is passed as the start routine to pthread_create. The function takes a single void * argument that is cast to an int * to obtain the number of iterations to perform. The main function creates two threads, each with a different number of iterations to perform, and waits for them to complete using pthread_join. The shared variable count is incremented in the increment_count function, which leads to a data race since both threads can access it concurrently.
*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *increment_count(void *arg) {
    int *num = (int *)arg;
    for (int i = 0; i < 2; i++) {
        *(num) = 0; // Data race
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t thread;

    int *arg = malloc(sizeof(int));
    pthread_create(&thread, NULL, increment_count, arg);

    *arg = 2;
    pthread_create(&thread, NULL, increment_count, arg);

    pthread_join(thread, NULL);
    printf("Final count: %d\n", *arg);

    return 0;
}
