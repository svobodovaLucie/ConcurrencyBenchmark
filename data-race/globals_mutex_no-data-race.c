/*
  Data race doesn't occur because the global mutex 
  is locked each time a global variable is accessed.
*/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_t t;
pthread_mutex_t m;
int i = 0;

void *foo(void *arg) {
  pthread_mutex_lock(&m);
  i = 42;
  pthread_mutex_unlock(&m);
}

int main() {
  pthread_create(&t, NULL, &foo, NULL);
  sleep(0.1);

  pthread_mutex_lock(&m);
  printf("%d\n", i);
  pthread_mutex_unlock(&m);
  
  pthread_join(t, NULL);
}