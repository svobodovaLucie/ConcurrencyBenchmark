#include <pthread.h>
#include <stdlib.h>

void *foo(void *arg) {
  int *i = (int *)arg;

  *i = 42;                                // data race
}

void *bar(void *arg) {
  pthread_t t1;
  int *x = malloc(sizeof(int));

  pthread_create(&t1, NULL, foo, x);

  *x = 0;                                 // data race

  pthread_join(t1, NULL);
}

int main() {
  pthread_t t;
  pthread_create(t, NULL, bar, NULL);

  return 0;
}