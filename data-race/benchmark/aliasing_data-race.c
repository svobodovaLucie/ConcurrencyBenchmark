#include <stdio.h>
#include <pthread.h>

pthread_t t;
int *p;
int i = 0;

void *foo(void *arg) { 
  int j = 42;
  p = &j;
  *p = 12;
  i = *p;
  int **q = &p;
  i = **q;
  **q = 9;
   p = &i;
}

int main() {
  int i = 0;
  p = &i;
  pthread_create(&t, NULL, foo, NULL);
  *p = 23; 
  pthread_join(t, NULL);
  return 0;
}
