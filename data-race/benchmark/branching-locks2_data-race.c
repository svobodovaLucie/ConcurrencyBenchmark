/*
  Data race on global variable without using locks.
*/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_t t;
pthread_mutex_t *m;
int i = 0;
int j = 0;

void *foo(void *arg) {
  pthread_mutex_lock(m);  // lockset: {m}

  if (i < 9) {
    pthread_mutex_unlock(m);  // lockset: {}
  }
  // else                   // lockset: {m}
  // -> after join: lockset: {} <- m may not be locked

  j = 9;  // lockset: {}
}

int main() {
  pthread_create(&t, NULL, &foo, NULL);

  pthread_mutex_lock(m);
  j = 0;
  pthread_mutex_unlock(m);

  pthread_join(t, NULL);
}
