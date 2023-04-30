#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct node {
  int value;
  struct node *next;
} node_t;

node_t *head = NULL;
pthread_mutex_t lock;

void add_to_list(int value) {
  node_t *new_node = malloc(sizeof(node_t));
  new_node->value = value;
  pthread_mutex_lock(&lock);
  new_node->next = head;
  head = new_node;
  pthread_mutex_unlock(&lock);
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
  pthread_mutex_init(&lock, NULL);

  pthread_create(&thread1, NULL, thread_func, &value1);
  pthread_create(&thread2, NULL, thread_func, &value2);

  pthread_join(thread1, NULL);
  pthread_join(thread2,NULL);

  pthread_mutex_destroy(&lock);
  print_list();

  return 0;
}
