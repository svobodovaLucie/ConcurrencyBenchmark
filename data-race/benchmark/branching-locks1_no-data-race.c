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
  if (i == 0) {
    pthread_mutex_lock(m);  // lockset: {m}
  } else {
    pthread_mutex_lock(m);  // lockset: {m}
  }
  // -> after join: lockset: {m} <- m must be locked

  j = 9;  // lockset: {}
}

int main() {
  pthread_create(&t, NULL, &foo, NULL);

  pthread_mutex_lock(m);
  j = 0;
  pthread_mutex_unlock(m);

  pthread_join(t, NULL);
}
