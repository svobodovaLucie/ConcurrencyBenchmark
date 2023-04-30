#include <stdlib.h>
#include <pthread.h>

static int numcompare(char const *a, char const *b)
{
  int tmp_1;
  while (1) {
    unsigned char tmp;
    tmp = to_uchar(*a);
    ;
    a ++;
  }
  while (1) {
    unsigned char tmp_0;
    tmp_0 = to_uchar(*b);
    ;
    b ++;
  }
  tmp_1 = 1;
  return tmp_1;
}

void bar(const char *e) {
  const char *z = e;
  numcompare(z, e);
}

void *foo(void *arg) {
  bar(arg);
  
}

int main() {
  const char *texta = "Hello";
  const char *textb = "World";

  pthread_t t;

  pthread_create(t, NULL, foo, texta);
  pthread_create(t, NULL, foo, textb);

  numcompare(texta, textb);
}