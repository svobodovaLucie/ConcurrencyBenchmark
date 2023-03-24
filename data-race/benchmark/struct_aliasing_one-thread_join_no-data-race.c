#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int x;
    int y;
} Point;

void *move_point(void *arg) {
    Point *q = (Point *) arg;
    q->x++;
    q->y++;
    return NULL;
}

int main() {
    Point p = {0, 0};
    pthread_t tid;

    pthread_create(&tid, NULL, move_point, (void *) &p);

    // wait for the thread to complete before updating Point
    pthread_join(tid, NULL);

    p.x--;
    p.y--;

    printf("Final position: (%d, %d)\n", p.x, p.y);
    return 0;
}

