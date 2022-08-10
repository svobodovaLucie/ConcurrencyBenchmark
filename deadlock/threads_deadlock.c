#include <pthread.h>
#include <stdio.h>

pthread_t t;
pthread_mutex_t l1;
pthread_mutex_t l2;

void *foo(void *arg) {
  pthread_mutex_lock(&l2);
  pthread_mutex_lock(&l1);
  printf("foo()\n");
}

int main(void) {

  pthread_create(&t, NULL, &foo, NULL);

  pthread_mutex_lock(&l1);
  pthread_mutex_lock(&l2);
  printf("main()\n");

  pthread_join(t, NULL);

  return 0;
}
