#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 10
int *idk;
int var = 9;

void modify_array(int *arr, int id) {
    arr[id] = 1;
    var = 8;
}

void *thread_func(void *arg) {
    int *my_array = (int *)arg;
    idk = my_array;
    int index = 0;
    while (1) {
        modify_array(my_array, index);
        index = (index + 1) % ARRAY_SIZE;
    }
    return NULL;
}

void foo(int *g) {
    g[0] = 3;
}

int main() {
    pthread_t thread1, thread2;
    int array[ARRAY_SIZE] = {0};

    pthread_create(&thread1, NULL, thread_func, array);
    pthread_create(&thread2, NULL, thread_func, array);

    foo(array);

    array[0] = 0;

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
