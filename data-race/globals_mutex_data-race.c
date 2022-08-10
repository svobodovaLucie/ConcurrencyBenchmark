/*
  Data race on global variable when using one mutex.
*/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_t t;
pthread_mutex_t m;
int i = 0;

void *foo(void *arg) {
  i = 42;
}

int main() {
  pthread_create(&t, NULL, &foo, NULL);
  
  sleep(0.1);

  pthread_mutex_lock(&m);
  printf("%d\n", i);
  pthread_mutex_unlock(&m);
  
  pthread_join(t, NULL);
}