#include <pthread.h>
#include <unistd.h>

pthread_t t, t1;
pthread_mutex_t *m;
int i = 0;
int j = 0;

void *bar(void *arg) {
  j = 5;
}

void *foo(void *arg) {
  if (i == 0) {
    pthread_create(&t1, NULL, &bar, NULL);  // threads_active: {t1}
    j = 9;
    pthread_join(t1, NULL);
  }
  // else                                   // threads_active: {}
  // -> after join: threads_active: {t1} <- t1 may be running
}

int main() {
  pthread_create(&t, NULL, &foo, NULL);

  pthread_join(t, NULL);
}
