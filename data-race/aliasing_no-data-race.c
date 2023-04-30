#include <stdio.h>
#include <pthread.h>

pthread_t t;
int *p;
int i = 0;
pthread_mutex_t mutex;

void *foo(void *arg) { 
  int j = 42;
  pthread_mutex_lock(&mutex);
  p = &j;
  *p = 12;
  p = &i;
  pthread_mutex_unlock(&mutex);
}

int main() {
  p = &i;
  pthread_mutex_init(&mutex, NULL);
  pthread_create(&t, NULL, foo, NULL);
  pthread_mutex_lock(&mutex);
  *p = 23; 
  pthread_mutex_unlock(&mutex);
  pthread_join(t, NULL);
  pthread_mutex_destroy(&mutex);
  return 0;
}

