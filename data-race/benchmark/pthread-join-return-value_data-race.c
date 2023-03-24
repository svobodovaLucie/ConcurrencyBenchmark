/*
In the increment_count function, a new integer variable ret is allocated on the heap and its value is set to the current value of count. This value is then returned from the thread using pthread_exit. In the main function, two threads are created and their return values are passed to pthread_join through pointer variables ret1 and ret2. Since these variables are shared between threads and main, there is a data race when accessing them.
*/

#include <stdio.h>
#include <pthread.h>

int count = 0;

void *increment_count(void *arg) {
    int num_iterations = *(int *)arg;
    for (int i = 0; i < num_iterations; i++) {
        count++;
    }
    int *ret = malloc(sizeof(int));
    *ret = count;
    pthread_exit(ret);
}

int main() {
    pthread_t thread1, thread2;
    int num_iterations = 10000;

    int arg = num_iterations;
    pthread_create(&thread1, NULL, increment_count, &arg);
    pthread_create(&thread2, NULL, increment_count, &arg);

    int *ret1, *ret2;
    pthread_join(thread1, (void **)&ret1);
    pthread_join(thread2, (void **)&ret2);

    printf("Thread 1 count: %d\n", *ret1); // Data race
    printf("Thread 2 count: %d\n", *ret2); // Data race
    printf("Final count: %d\n", count);

    free(ret1);
    free(ret2);
    return 0;
}
