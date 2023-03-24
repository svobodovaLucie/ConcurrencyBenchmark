#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

pthread_t t;
int *i;

void *foo(void *arg) {
  *i = 19;    // data race
}

int main() {
  i = malloc(sizeof(int *));
  *i = 23;

  int *j = i;

  pthread_create(&t, NULL, &foo, NULL);
  
  *j = 42;    // data race
  
  sleep(0.1);
  printf("%d\n", *i);   // data race
  
  pthread_join(t, NULL);
}