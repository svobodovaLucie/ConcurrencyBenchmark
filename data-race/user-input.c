#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int global_value = 0;

void *thread_func(void *arg) {
    int *my_value = (int *)arg;
    global_value += *my_value;
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    int input_value;

    printf("Enter an integer value: ");
    scanf("%d", &input_value);

    pthread_create(&thread1, NULL, thread_func, &input_value);
    pthread_create(&thread2, NULL, thread_func, &input_value);

    pthread_join(thread1, NULL);
    pthread_join(thread2,NULL);

    printf("Final value: %d\n", global_value);

    return 0;
}
