#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static void sortlines(int *a);

static void *sortlines_thread(void *data)
{
  void *__retres;
  int *args = (int*)data;
  sortlines(args);
  __retres = (void *)0;
  return __retres;
}

static void sortlines(int *a) {
  pthread_t thread, thread2;
  *a = 8;
  pthread_create(& thread,(void *)0,& sortlines_thread,&a);
  pthread_create(& thread2,(void *)0,& sortlines_thread,&a);
}

int main() {
  int *b = malloc(sizeof(int));
  sortlines(b);
}