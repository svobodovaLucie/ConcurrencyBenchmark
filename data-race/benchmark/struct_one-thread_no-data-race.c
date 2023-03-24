#include <stdio.h>
#include <pthread.h>

typedef struct {
    int x;
    int y;
} Point;

Point p = {0, 0};
pthread_t tid;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *move_point(void *arg) {
    pthread_mutex_lock(&mutex);
    p.x++;
    p.y++;
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_mutex_lock(&mutex);
    p.x--;
    p.y--;
    pthread_mutex_unlock(&mutex);

    pthread_create(&tid, NULL, move_point, NULL);

    pthread_join(tid, NULL);

    pthread_mutex_lock(&mutex);
    printf("Final position: (%d, %d)\n", p.x, p.y);
    pthread_mutex_unlock(&mutex);
    return 0;
}

