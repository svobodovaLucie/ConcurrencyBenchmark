#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct node {
    int value;
    struct node *next;
} node_t;

node_t *head = NULL;

void add_to_list(int value) {
    node_t *new_node = malloc(sizeof(node_t));
    new_node->value = value;
    new_node->next = head;
    head = new_node;
}

void *thread_func(void *arg) {
    int *my_value = (int *)arg;
    for (int i = 0; i < 5; i++) {
        add_to_list(*my_value);
    }
    return NULL;
}

void print_list() {
    node_t *current = head;
    printf("List: ");
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

int main() {
    pthread_t thread1, thread2;
    int value1 = 1, value2 = 2;

    pthread_create(&thread1, NULL, thread_func, &value1);
    pthread_create(&thread2, NULL, thread_func, &value2);

    pthread_join(thread1, NULL);
    pthread_join(thread2,NULL);

    print_list();

    return 0;
}
