#include <stdio.h>
#include <pthread.h>

int counter = 0;

void *increment_counter(void *arg) {
    counter = 42;	// data race on thread1 and thread2
}

void *foo(void *arg) {
    pthread_t thread1, thread2;
    
    printf("Counter value: %d\n", counter);	// no data race

    pthread_create(&thread1, NULL, increment_counter, NULL);
    pthread_create(&thread2, NULL, increment_counter, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Counter value: %d\n", counter);	// no data race
}

int main() {
    pthread_t t;
    
    pthread_create(&t, NULL, foo, NULL);
    
    return 0;
}
