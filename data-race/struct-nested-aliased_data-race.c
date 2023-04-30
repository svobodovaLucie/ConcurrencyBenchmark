#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct nested_struct {
    int value;
};

struct my_struct {
    struct nested_struct *ptr;
};

void *thread_func(void *arg) {
    struct my_struct *e = (struct my_struct *)arg;
    e->ptr->value += 1;
    return NULL;
}

int main() {
    struct nested_struct nested = {0};
    struct my_struct s = {&nested};
    struct my_struct *p = &s;

    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, thread_func, &s);
    pthread_create(&thread2, NULL, thread_func, p);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Final value: %d\n", s.ptr->value);

    return 0;
}
