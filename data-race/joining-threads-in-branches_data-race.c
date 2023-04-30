#include <pthread.h>

pthread_t t1;
int x;

void *thread1(void *arg) {
  x = 8;
}

void f() {
  x = 0;
}

void g() {
  for (int i = 0; i < 10; i++) {
    pthread_create(&t1, NULL, thread1, NULL);
  }
  
  f();
}

int main() {

  g();

}