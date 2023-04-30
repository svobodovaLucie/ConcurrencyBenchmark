#include <pthread.h>
#include <assert.h>

#define BUFFER_MAX  10
#define N 7
#define ERROR -1
#define FALSE 0
#define TRUE 1

static char  buffer[BUFFER_MAX];     /* BUFFER */

static unsigned int first;
static unsigned int next;
static int  buffer_size;

_Bool send, receive;

pthread_mutex_t m;

int insertLogElement(int b) 
{
  if (next < buffer_size && buffer_size > 0) 
  {
    buffer[next] = b;
    next = (next+1)%buffer_size;
    assert(next<buffer_size);
  } 
  else 
  {
    return ERROR;
  }

  return b;
}

void *t1(void *arg) 
{
  int i;

  for(i=0; i<N; i++)
  {
    pthread_mutex_lock(&m);
    if (send) 
    {
      insertLogElement(i);
      send=FALSE;
      receive=TRUE;
    }
    pthread_mutex_unlock(&m);
  }  
}

void *t2(void *arg) 
{
  int i;

  for(i=0; i<N; i++)
  {
    pthread_mutex_lock(&m);
    if (receive) 
    {
      assert(removeLogElement()==i);
      receive=FALSE;
      send=TRUE;
    }
    pthread_mutex_unlock(&m);
  }
}

int main() 
{
  pthread_t id1, id2;

  pthread_mutex_init(&m, 0);

  initLog(10);
  send=TRUE;
  receive=FALSE;

  pthread_create(&id1, NULL, t1, NULL);
  pthread_create(&id2, NULL, t2, NULL);

  pthread_join(id1, NULL);
  pthread_join(id2, NULL);

  return 0;
}


