#include <pthread.h>
#include <stdio.h>

pthread_mutex_t *l;
int running = 0;

int pthread_lock(pthread_mutex_t *m)
{
  pthread_mutex_lock(m);
}

void *cascade(void *arg)
{
  running++;
}

void foo() {
  pthread_t tid;
  pthread_lock(l);
  
}


int main() {

  foo();
  running = 9;
}