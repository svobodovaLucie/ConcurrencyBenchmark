/*
This program creates two threads that both increment a shared variable counter by 1 million times. The problem with this program is that both threads access the counter variable concurrently without any synchronization mechanism to ensure that only one thread can access it at a time. This leads to a data race, where the value of counter can be incremented inconsistently due to the interleaving of the two threads' execution.

As a result, the final value of counter that is printed out may be less than the expected value of 2 million, since some of the increments may be lost due to the data race. To fix this, we need to use synchronization mechanisms such as mutexes or atomic operations to ensure that only one thread can access the counter variable at a time.
*/

#include <stdio.h>
#include <pthread.h>

int counter = 0;

void *increment_counter(void *arg) {
    counter = 42;		// data race
}

void *foo(void *arg) {
    pthread_t thread1, thread2;
    
    printf("Counter value: %d\n", counter);	// no data race

    pthread_create(&thread1, NULL, increment_counter, NULL);
    
    counter = 8;		// data race

    pthread_join(thread1, NULL);		

    printf("Counter value: %d\n", counter);	// no data race
}

int main() {
    pthread_t t;
    
    pthread_create(&t, NULL, foo, NULL);
    
    return 0;
}
