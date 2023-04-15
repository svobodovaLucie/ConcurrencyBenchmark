#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_t t;
pthread_mutex_t *m;
int **p;
int a = 19;
int b = 23;
int c = 42;
int *i;
int *j;

void *foo(void *arg) {
  //int *i;
  //int *j;
                            // aliases:
  if (b >= 2) {
    i = &a;                 // (i, &a)
  } else {
    i = &b;                 // (i, &b)
  }                         // -> after join: {(i, &a), (i, &b)}

  j = &c;                   // {(i, &a), (i, &b), (j, &c)}

  if (a > 8) {
    p = &i;                 // (p, &i) 
  } else {
    p = &j;                 // (p, &j)
  }                         // -> after join: {(p, &i), (p, &j),
                            //                 (i, &a), (i, &b), 
                            //                 (j, &c)}

  printf("%d\n", *i);       // access to: i, a, b
  printf("%d\n", **p);      // access to: p, i, j, a, b, c
}

int main() {
  pthread_create(&t, NULL, &foo, NULL);
                            // accesses to:
  a = 8;                    // a
  b = 9;                    // b
  c = 10;                   // c

  pthread_join(t, NULL);
}
