#include <stdio.h>
#include <pthread.h>

typedef struct {
    int x;
    int y;
} Point;

Point p = {0, 0};
pthread_t tid;

void *move_point(void *arg) {
    // Data race occurs here
    p.x++;
    p.y++;
    return NULL;
}

int main() {
    pthread_create(&tid, NULL, move_point, NULL);    
    // Data race occurs here
    p.x--;
    p.y--;

    pthread_join(tid, NULL);

    printf("Final position: (%d, %d)\n", p.x, p.y);
    return 0;
}

