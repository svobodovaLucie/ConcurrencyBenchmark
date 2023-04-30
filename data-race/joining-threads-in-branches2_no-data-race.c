#include <pthread.h>

pthread_t t1;
int x;

void *thread1(void *arg) {
  x = 8;
}

void f() {
  if (1) {
    pthread_join(t1, NULL);
  } else {
    pthread_join(t1, NULL);
  }
  x = 0;
}

void g() {
  pthread_create(&t1, NULL, thread1, NULL);
  
  f();
}

int main() {

  g();

}