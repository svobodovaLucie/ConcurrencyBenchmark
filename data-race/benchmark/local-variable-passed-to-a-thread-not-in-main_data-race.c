#include <stdio.h>
#include <pthread.h>

pthread_t thread;

void *increment_count(void *arg) {
    int *r = (int *)arg;  // l th23, z th13
    *r = 6;		  // l th23, *l th23, z th13, *z th13
}

void foo() {
    int *z = malloc(sizeof(int)); // z m, {m,t1}
    pthread_create(&thread, NULL, increment_count, z); // z m, {m,t1,t2}
    *z = 0; // z main, *z main
}

int main() {
  
    int l = 9;
    int m = 2;
    printf("%d %d", l, m);
   
    pthread_create(&thread, NULL, increment_count, &l);
    
    foo();
    
    l = 8; // l main
    m = 7; // main
    
    return 0;
}

/*
Data Race:
- l 27 main a 8 th23
- z 14 main a 8 th13
PS. pozor na z/*z, *l/l/&l
*/

/*
TODO
- hlasi to data race na radcich 7 a 12,
  ale na radku 7 jeste nebylo spusteno vlakno thread! a tim padem tam nemuze byt data race
- naopak by mel byt na radcich 7 a 14 a 8 a 14, protoze v obou pripadech se cte promenna z (ne jen *z)
*/
