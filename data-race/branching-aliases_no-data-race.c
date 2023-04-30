#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_t t;
pthread_mutex_t *m;
int **p;
int a = 19;
int b = 23;
int c = 42;

void *foo(void *arg) {      // aliases:
  int *i;
  int *j;

  if (b >= 2) { // b, rd
    i = &a;                 // (i, &a)
  } else {
    i = &b;                 // (i, &b)
  }                         // -> after join: {(i, &a), (i, &b)}

  j = &c;                   // {(i, &a), (i, &b), (j, &c)}

  if (c > 8) {  // c, rd
    p = &i;                 // (p, &i) 
  } else {
    p = &j;                 // (p, &j)
  }                         // -> after join: {(p, &i), (p, &j)}

  //printf("%d\n", **p);

  int *z;
  p = &z;     // p, wr      // aliasy p odstranit a pridat (p, &z)

  p = NULL;                 // aliasy p odstranit uplne

  printf("%d\n", **p);

  **p = 3;
}

int main() {
  pthread_create(&t, NULL, &foo, NULL);

  a = 7;

  pthread_join(t, NULL);
}
