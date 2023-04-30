/*
The data race in this program occurs on the shared variable `available`, which is accessed by all three threads. The threads access the `available` variable without any mutual exclusion, so a data race occurs. This data race can lead to incorrect results if two or more threads try to modify the `available` variable simultaneously. To fix this issue, we can use a mutex to protect the `available` variable, so that only one thread can modify it at a time.

In this program, the bank has 3 resources and 3 customers. Each customer makes a request for resources, and the banker checks if the request can be granted without violating the safety algorithm. The program contains a data race on the shared variable available that keeps track of the available resources.
*/

#include <stdio.h>
#include <pthread.h>

void *customer(void *arg) {
    int id = *(int *)arg;	// no pointer -> no aliasing
    id = 9;
}

int main() {
    pthread_t threads[3];
    int ids[3] = { 0, 1, 2 };
    
    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, customer, &ids[i]);
    }
//    ids = 9;
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}
