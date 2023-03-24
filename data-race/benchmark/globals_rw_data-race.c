/*
  Data race on global variable without using locks.
*/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_t t;
int i = 0;

void *foo(void *arg) {
  printf("Hello from foo\n");

  i = 42;    // 1

  printf("%d\n", i); //i = 19;    // 2
}

/*
summary foo:
{
  (i, 15, wr, O, O, O, -);
  (i, 17, wr, O, O, O, -);
}
*/

void bar () {
  printf("Hello from bar\n");
}

/*
summary bar:
{}
*/

int main() {
  //printf("Hello from main\n");
  pthread_create(&t, NULL, &foo, NULL);
  sleep(0.1);
  
  //printf("%d\n", i);
  i = 23;    // 3
  
  pthread_join(t, NULL);

  i = 666;    // 4

  // TODO remove
  //pthread_create(&t, NULL, &foo, NULL);

  //bar();
}

/*
summary main:
{
  integrate foo:
  1. (i, 15, wr, O, O, {main, t}, t);
  2. (i, 17, wr, O, O, {main, t}, t);
  3. (i, 43, wr, O, O, {main, t}, main);
  4. (i, 47, wr, O, O, {main}, main);
}
*/

/*
main analysis:
- kazdy s kazdym pomoci prochazeni seznamu?
  neco jako vnoreny for
- co checkujeme u kazdeho paru?
ukazka pristupu: (v, l, a, l, u, ts, t)

1 a 2:
  stejna promenna? v1 == v2: 1
  a1 != rd and a2 != rd: 1
  t1 == t2 -> no data race
  a0 b0 c0 d1 -> no data race

1 a 3:
  a0 b0 c0 d0 e0 f0 -> data race

1 a 4:
  a0 b0 c0 d0 e1 -> no data race

2 a 3:
  a0 b0 c0 d0 e0 f0 -> data race

2 a 4:
  a0 b0 c0 d0 e1 -> no data race

3 a 4:
  a0 b0 c0 d1 -> no data race
  
  
celkovy algoritmus:
  pred vstupem do vnitrniho foru checknout podminky:
    a) if pocet clenu (ts1) < 2 then next
  vnoreny for:
    b) if v1 != v2 then next
    c) if a1 == rd and a2 == rd then next
    d) if t1 == t2 then next
    e) if ts1 podmnozina? rovna se jen main? obsahuje jen jeden prvek spolecny? ts2 then next
      (if pocet prvku v pruniku >= 2)
      -> asi: if pocet clenu (prunik ts1 ts2) < 2 then next
    f) if l1 prunik neni prazdny l2 then next (if prunik je prazdny)
    if u1 ... u2 then next (unlockset mi je asi jedno?)
*/
