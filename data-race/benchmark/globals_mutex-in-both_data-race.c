/*
  Data race on global variable when using one mutex.
*/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 

pthread_t t;
pthread_mutex_t m;
int i = 0;

void *foo(void *arg) {
  pthread_mutex_lock(&m);
  int *p = (int *)arg;
  *p = 23;
  pthread_mutex_unlock(&m);
}

int main() {

  int i = 0;
  
  pthread_create(&t, NULL, &foo, (int *)&i);
  sleep(0.001);
  i = 42;

  pthread_join(t, NULL);
  
  printf("%d\n", i);
}
