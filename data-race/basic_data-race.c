/*
This program creates two threads that both increment a shared variable counter by 1 million times. The problem with this program is that both threads access the counter variable concurrently without any synchronization mechanism to ensure that only one thread can access it at a time. This leads to a data race, where the value of counter can be incremented inconsistently due to the interleaving of the two threads' execution.

As a result, the final value of counter that is printed out may be less than the expected value of 2 million, since some of the increments may be lost due to the data race. To fix this, we need to use synchronization mechanisms such as mutexes or atomic operations to ensure that only one thread can access the counter variable at a time.
*/

#include <stdio.h>
#include <pthread.h>

int counter = 0;

void *increment_counter(void *arg) {
    int i;
    //for (i = 0; i < 1000000; i++) {
    //    counter++;
    //}
    counter = 42;
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, increment_counter, NULL);
    pthread_create(&thread2, NULL, increment_counter, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Counter value: %d\n", counter);

    counter = 8;
    
    return 0;
}
