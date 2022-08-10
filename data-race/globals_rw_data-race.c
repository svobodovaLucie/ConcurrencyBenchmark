/*
  Data race on global variable without using locks.
*/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_t t;
int i = 0;

void *foo(void *arg) {
  i = 42;
}

int main() {
  pthread_create(&t, NULL, &foo, NULL);
  sleep(0.1);
  
  printf("%d\n", i);
  
  pthread_join(t, NULL);
}