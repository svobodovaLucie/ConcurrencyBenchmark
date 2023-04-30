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
  int *j = malloc(sizeof(int));
  if (j == NULL)
    return NULL;
  *j = 42;
  i = *j;
}

int main() {
  pthread_create(&t, NULL, &foo, NULL);

  pthread_mutex_lock(&m);
  i = 19;
  //printf("%d\n", i);
  pthread_mutex_unlock(&m);

  //sleep(0.001);
  i = 23;
  
  pthread_join(t, NULL);
  
  //printf("%d\n", i);

  //i = 666;
}
