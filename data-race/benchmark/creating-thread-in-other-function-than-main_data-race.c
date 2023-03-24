#include <stdio.h>
#include <pthread.h>

int j = 0;

pthread_t thread;

void *increment_count(void *arg) {
    int *r = (int *)arg;
    *r = 6;
    j = 42;
    printf("j: %d\n", j);
}

void foo() {
    int *z = malloc(sizeof(int));
    pthread_create(&thread, NULL, increment_count, z);
    *z = 0;
}

int main() {
    
    foo();
    
    return 0;
}
