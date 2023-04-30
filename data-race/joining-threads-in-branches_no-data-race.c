#include <pthread.h>

pthread_t t1;
int x;

void *thread1(void *arg) {
  x = 8;
}

void f() {
  for (int i = 0; i < 10; i++) {
    pthread_join(t1, NULL);
  }
  x = 0;  // no data race
}

void g() {
  for (int i = 0; i < 10; i++) {
    pthread_create(&t1, NULL, thread1, NULL);
  }
  
  f();  // joining threads
}

int main() {

  g();

}