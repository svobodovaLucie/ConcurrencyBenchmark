#include <pthread.h>

pthread_t t1;
int x;

void *thread1(void *arg) {
  x = 8;
}

void f() {
  pthread_join(t1, NULL); // (t1, -1)

  x = 0;  // no data race
}

void g() {
  pthread_create(&t1, NULL, thread1, NULL);
  
  //pthread_join(t1, NULL);

  f();  // joining threads
}

int main() {

  g();

}