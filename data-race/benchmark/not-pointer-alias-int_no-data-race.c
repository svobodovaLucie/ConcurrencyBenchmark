#include <stdio.h>
#include <pthread.h>

void *customer(void *arg) {
    int id = *(int *)arg; // no pointer -> no aliasing!
    id = 9;
}

int main() {
    pthread_t threads[3];
    int ids;
    
    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, customer, ids);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}
