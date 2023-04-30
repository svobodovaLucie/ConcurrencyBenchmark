#include <pthread.h>
#include <assert.h>

pthread_t id1, id2;
pthread_mutex_t *m;
int i;

void *t1(void *arg) 
{
  pthread_mutex_lock(m); 
  i = 0;
  pthread_mutex_unlock(m);
}

void release() {
  pthread_mutex_unlock(m);
}

void acquire() {
  pthread_mutex_lock(m);
}

void foo() {
  acquire();
  release();

  i = 8;
}

int main() 
{
  pthread_create(&id1, NULL, t1, NULL);

  foo();

  pthread_join(id1, NULL);

  return 0;
}


