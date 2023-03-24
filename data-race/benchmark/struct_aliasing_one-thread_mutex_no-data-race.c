#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int x;
    int y;
} Point;

pthread_mutex_t mutex;

void *move_point(void *arg) {
    Point *q = (Point *) arg;
    pthread_mutex_lock(&mutex);
    q->x++;
    q->y++;
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    Point p = {0, 0};
    pthread_t tid;

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&tid, NULL, move_point, (void *) &p);

    pthread_mutex_lock(&mutex);
    p.x--;
    p.y--;
    pthread_mutex_unlock(&mutex);

    pthread_join(tid, NULL);

    printf("Final position: (%d, %d)\n", p.x, p.y);

    pthread_mutex_destroy(&mutex);

    return 0;
}

