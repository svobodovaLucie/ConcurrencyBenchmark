#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

pthread_t t;
pthread_mutex_t *m;
int **p;
int a = 19;
int b = 23;
int c = 42;
int *i;
int *j;

void *foo(void *arg) {

  i = malloc(sizeof(int));  // aliases: {}, heap: {(i, 16)}

  i = &b;

  if (b >= 2) {
    i = &a;                 // aliases: {(i, &a)}, heap: {}
  } else {
    b = 7;                  // aliases: {}, heap: {(i, 16)}
  }                         // -> after join: aliases: {(i, &a)}, heap: {(i, 16)}

  j = &c;                   // aliases: {(i, &a), (j, &c)}, heap: {(i, 16)}

  if (a > 8) {
    p = &i;                 // aliases: {(p, &i), (i, &a), (j, &c)}, heap: {(i, 16)}
  } else {
    p = &j;                 // aliases: {(p, &j), (i, &a), (j, &c)}, heap: {(i, 16)}
  }                         // -> after join: aliases: {(p, &i), (p, &j),
                            //                          (i, &a), (j, &c)},
                            //                heap: {(i, 16)}

  printf("%d\n", *i);       // access to: i, a, b
  printf("%d\n", **p);      // access to: p, i, j, a, b, c
}

int main() {
  pthread_create(&t, NULL, &foo, NULL);

  i = &a;

  *i = 8;
                            // accesses to:
  a = 8;                    // a
  b = 9;                    // b
  c = 10;                   // c

  pthread_join(t, NULL);
}
