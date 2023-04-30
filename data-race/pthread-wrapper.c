#include <pthread.h>
#include <stdio.h>

int running = 0;

int pthread_create0(pthread_t *thread, pthread_attr_t const *attr,
                    void *(*start_routine)(void *), void *arg)
{
  int err;
  int retry = 10;
  int tmp_1;
  int tmp;
  pthread_create(thread, attr, start_routine, arg);
  tmp = pthread_create(thread,attr,start_routine,arg);
  if (tmp) {
    int tmp_0;
    tmp_0 = retry;
    retry --;
    ;
    if (tmp_0) tmp_1 = 1; else tmp_1 = 0;
  }
  else tmp_1 = 0;
  err = tmp_1;
  sched_yield();
  return err;
}

void *cascade(void *arg)
{
  running++;
}

void foo() {
  pthread_t tid;
  pthread_create0(&tid,NULL,&cascade,NULL);
  pthread_create(&tid,NULL,&cascade,NULL);
}


int main() {

  foo();
  running = 9;
}