#include <stdio.h>
#include <pthread.h>

int j = 0;

pthread_t thread;

void *increment_count(void *arg) {
    j = 42;
}

int main() {
   
    for (int i = 0; i < 2; i++) {
        pthread_create(&thread, NULL, increment_count, NULL);
    }

    j = 23;
    
    for (int i = 0; i < 2; i++) {
        pthread_join(thread, NULL);
    }
    
    return 0;
}
