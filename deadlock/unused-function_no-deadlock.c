#include <pthread.h>
#include <stdio.h>

pthread_mutex_t l1;
pthread_mutex_t l2;

void foo(void) {    // this function is not used
  pthread_mutex_lock(&l2);
  pthread_mutex_lock(&l1);
  printf("foo()\n");
}

int main(void) {

  pthread_mutex_lock(&l1);
  pthread_mutex_lock(&l2);
  printf("main()\n");

  return 0;
}
