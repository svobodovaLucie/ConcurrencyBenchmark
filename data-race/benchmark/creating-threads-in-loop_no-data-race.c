#include <stdio.h>
#include <pthread.h>

int j = 0;

pthread_t thread;
pthread_mutex_t m;

void *increment_count(void *arg) {
    
    pthread_mutex_lock(&m);
    
    j = 42;
    printf("j: %d\n", j);
    
    pthread_mutex_unlock(&m);
}

int main() {
    
    for (int i = 0; i < 2; i++) {
        pthread_create(&thread, NULL, increment_count, NULL);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(thread, NULL);
    }
    
    return 0;
}
