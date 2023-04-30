#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int x;
    int y;
} Point;

void *move_point(void *arg) {
    // Data race occurs here
    Point *q = (Point *) arg;
    q->x++;
    q->y++;
    return NULL;
}

int main() {
    Point p = {0, 0};
    pthread_t tid;

    // Data race occurs here
    pthread_create(&tid, NULL, move_point, (void *) &p);
    p.x--;
    p.y--;

    pthread_join(tid, NULL);

    printf("Final position: (%d, %d)\n", p.x, p.y);
    return 0;
}

