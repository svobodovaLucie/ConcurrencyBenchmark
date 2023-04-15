#include <pthread.h>
#include <unistd.h>

pthread_t t, t1;
pthread_mutex_t *m;
int i = 0;
int j = 0;

void *bar(void *arg) {
  j = 5;
}

int main() {
  if (i == 0) {
    pthread_create(&t1, NULL, &bar, NULL);  // threads_active: {t1}
  }

  

  pthread_join(t1, NULL);

  j = 9;
}
