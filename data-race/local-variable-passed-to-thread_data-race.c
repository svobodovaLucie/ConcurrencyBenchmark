#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void *print_message(void *arg) {
    printf("arg=%p\n", arg);
    int *val = (int *) arg;
    printf("The value passed to the thread is %d\n", *val);
    *val = *val + 1;
    pthread_exit(NULL);
}

int main() {
    pthread_t tid;
    int value = 0;

    pthread_create(&tid, NULL, print_message, &value);
    printf("&value=%p\n", &value);
   
    usleep(0.1);
    value = 42;
    
    pthread_join(tid, NULL);

    printf("The value after the thread execution is %d\n", value);

    return 0;
}

