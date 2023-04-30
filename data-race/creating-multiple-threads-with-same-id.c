#include <pthread.h>

pthread_t threads[2];
int x;

void *thread1(void *arg) {
  x = 8;
}

void f() {
  pthread_join(threads[0], NULL);

  pthread_join(threads[1], NULL);

  pthread_join(threads[2], NULL);

  x = 0;  // no data race
}

void g() {

  pthread_create(&threads[0], NULL, thread1, NULL);

  pthread_create(&threads[1], NULL, thread1, NULL);

  pthread_create(&threads[2], NULL, thread1, NULL);

  f();
}

int main() {

  g();

}