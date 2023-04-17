/*
This program creates a linked list with a single node, and then creates two threads that both increment the value of the head node's value field. The problem with this program is that both threads access the value field via a pointer to the head node, without any synchronization mechanism to ensure that only one thread can access it at a time. This leads to a data race, where the value of value can be incremented inconsistently due to the interleaving of the two threads' execution.

As a result, the final value of value that is printed out may be less than the expected value of 2 million, since some of the increments may be lost due to the data race. To fix this, we need to use synchronization mechanisms such as mutexes or atomic operations to ensure that only one thread can access the value field at a time.
*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *next;
};

void *write_to_node_value(void *arg) {
    struct node *mad = (struct node *)arg;
    int k;
    int i;
    for (i = 0; i < 10; i++) {
        mad->value = 1;                // data race
    }
    return NULL;
}

void foo(int val) {
    printf("%d", val);                  // data race
}

int main() {
    struct node *head = malloc(sizeof(struct node));
    head->value = 0;
    head->next = NULL;
    struct node **tail = &head;

    pthread_t thread1, thread2;

    pthread_create(&thread2, NULL, write_to_node_value, head);

    foo((*tail)->value);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Head node value: %d\n", head->value);

    return 0;
}
