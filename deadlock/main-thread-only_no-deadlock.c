#include <pthread.h>
#include <stdio.h>

pthread_mutex_t l1;
pthread_mutex_t l2;

void foo(void) {
  pthread_mutex_lock(&l2);
  pthread_mutex_lock(&l1);
  printf("foo()\n");
  pthread_mutex_unlock(&l1);
  pthread_mutex_unlock(&l2);
}

int main(void) {

  foo();

  // the locks are unlocked at this point

  pthread_mutex_lock(&l1);
  pthread_mutex_lock(&l2);
  printf("main()\n");
  pthread_mutex_unlock(&l2);
  pthread_mutex_unlock(&l1);

  return 0;
}
