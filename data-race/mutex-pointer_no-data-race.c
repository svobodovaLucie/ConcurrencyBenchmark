#include <stdlib.h>
#include <pthread.h>

pthread_t t;

pthread_mutex_t l;
pthread_mutex_t *m;
pthread_mutex_t **p;

int i;
int j;
int k;

void *foo(void *arg) {
  pthread_mutex_lock(&l);
  i = 19;
  pthread_mutex_unlock(&l);

  pthread_mutex_lock(m);
  j = 23;
  pthread_mutex_unlock(m);

  pthread_mutex_lock(*p);
  k = 42;
  pthread_mutex_unlock(*p);
}

int main() {
  pthread_create(&t, NULL, &foo, NULL);

  pthread_mutex_lock(&l);
  i = 19;
  pthread_mutex_unlock(&l);

  pthread_mutex_lock(m);
  j = 23;
  pthread_mutex_unlock(m);

  pthread_mutex_lock(*p);
  k = 42;
  pthread_mutex_unlock(*p);

  pthread_join(t, NULL);
}