#include <stdio.h>
#include <pthread.h>

pthread_t t;
int *p;
int i = 0;
int j = 42;

void *foo(void *arg) { 
  //int j = 42;
  p = &j;             // {(p, &j)}
  *p = 12;  // j
  i = *p;   // i, p, j
  int **q = &p;       // {(p, &j), (q, &p)}
  i = **q;  // i, q, p, j
  **q = 9;  // q, p, j
  p = &i;             // {(q, &p), (p, &i)}
}

int main() {
  int i = 0;
  p = &i;             // (p, &i)
  pthread_create(&t, NULL, foo, NULL);
  *p = 23;  // p, i
  pthread_join(t, NULL);
  return 0;
}
