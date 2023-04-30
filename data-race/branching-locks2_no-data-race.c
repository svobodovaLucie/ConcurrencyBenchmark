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

  j = 9;                  // lockset: {m}
}

int main() {
  pthread_create(&t, NULL, &foo, NULL);

  pthread_mutex_lock(m);
  j = 0;                  // lockset: {m}
  pthread_mutex_unlock(m);

  pthread_join(t, NULL);
}
