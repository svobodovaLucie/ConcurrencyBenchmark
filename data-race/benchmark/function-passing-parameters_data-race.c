/*
This program creates two threads that both call the function call_call_increment_value(), which in turn calls the function call_increment_value(), which finally calls the function increment_value(). The increment_value() function increments the value of the value variable by 1 million. The problem with this program is that both threads access the value variable without any synchronization mechanism to ensure that only one thread can access it at a time. This leads to a data race, where the value of value can be incremented inconsistently due to the interleaving of the two threads' execution.

As a result, the final value of value that is printed out may be less than the expected value of 2 million, since some of the increments may be lost due to the data race. To fix this, we need to use synchronization mechanisms such as mutexes or atomic operations to ensure that only one thread can access the value variable at a time.
*/

#include <stdio.h>
#include <pthread.h>

void increment_value(int *ptr) {
    int i;
    for (i = 0; i < 1000000; i++) {
        (*ptr)++;
    }
}

void call_increment_value(int *ptr) {
    increment_value(ptr);
}

void call_call_increment_value(int *ptr) {
    call_increment_value(ptr);
}

int main() {
    int value = 0;
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, (void *)call_call_increment_value, &value);
    pthread_create(&thread2, NULL, (void *)call_call_increment_value, &value);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Value: %d\n", value);

    return 0;
}
