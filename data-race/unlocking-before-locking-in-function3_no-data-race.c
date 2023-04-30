#include <pthread.h>
#include <assert.h>

pthread_t id1, id2;
pthread_mutex_t *m;
int i;
int j;

void *t1(void *arg) 
{
  pthread_mutex_lock(m); 
  i = 0;
  pthread_mutex_unlock(m);
}

void u() {
  i = 0;
  pthread_mutex_unlock(m);
}

void y() {
  pthread_mutex_lock(m);
  u();
}

int main() 
{
  pthread_create(&id1, NULL, t1, NULL);

  y();

  pthread_join(id1, NULL);

  return 0;
}


