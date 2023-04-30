/*
  Data race on global variable without using locks.
*/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

pthread_t t;
int *i;

void *foo(void *arg) {
  printf("i11: %d\n", *i);    // 01: (*i, 14, read)
  *i = 23;                    // 02: (*i, 15, write)      
  //int j = 19;                 

  int **p = malloc(sizeof(int *));  // 03: (**p, 18, write)
  *p = i;                           // 04: (*p, 19, write), 
                                    // 05: (i, 19, read)
  **p = 666;                        // 06: (**p, 21, write)

  printf("i12: %d, p12: %d\n", *i, **p); // 07: (*i, 23, read),
                                         // 08: (**p, 23, read)
}

int main() {
  //printf("Hello from main\n");
  i = malloc(sizeof(int));    // 1: (i, 35, write)
  if (i == NULL) {            // 2: (i, 36, read)
    return 1;
  }

  *i = 42;                    // 3: (*i, 40, write)
  printf("i1: %d\n", *i);     // 4: (*i, 41, read)

  pthread_create(&t, NULL, &foo, NULL);   // t
  sleep(0.1);
  
  printf("i2: %d\n", *i);         // 5: (*i, 46, read) !!!
  // i = 23;    // 3
  
  pthread_join(t, NULL);      // end t

  printf("i3: %d\n", *i);     // 6: (*i, 51, read)
}

/*
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
