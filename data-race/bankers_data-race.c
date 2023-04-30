/*
The data race in this program occurs on the shared variable `available`, which is accessed by all three threads. The threads access the `available` variable without any mutual exclusion, so a data race occurs. This data race can lead to incorrect results if two or more threads try to modify the `available` variable simultaneously. To fix this issue, we can use a mutex to protect the `available` variable, so that only one thread can modify it at a time.

In this program, the bank has 3 resources and 3 customers. Each customer makes a request for resources, and the banker checks if the request can be granted without violating the safety algorithm. The program contains a data race on the shared variable available that keeps track of the available resources.
*/

#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

int available[3] = { 10, 5, 7 };
int max[3][3] = {
    { 6, 3, 4 },
    { 4, 2, 3 },
    { 2, 2, 2 }
};
int allocation[3][3] = {
    { 3, 1, 2 },
    { 1, 1, 0 },
    { 1, 0, 1 }
};
int need[3][3];

bool is_safe() {
    int work[3];
    bool finish[3] = { false, false, false };
    for (int i = 0; i < 3; i++) {
        work[i] = available[i];
    }
    int count = 0;
    while (count < 3) {
        bool found = false;
        for (int i = 0; i < 3; i++) {
            if (!finish[i]) {
                bool can_be_allocated = true;
                for (int j = 0; j < 3; j++) {
                    if (need[i][j] > work[j]) {
                        can_be_allocated = false;
                        break;
                    }
                }
                if (can_be_allocated) {
                    for (int j = 0; j < 3; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    count++;
                    found = true;
                }
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}

void *customer(void *arg) {
    int id = *(int *)arg;
    int request[3];
    request[0] = rand() % (max[id][0] - allocation[id][0] + 1);
    request[1] = rand() % (max[id][1] - allocation[id][1] + 1);
    request[2] = rand() % (max[id][2] - allocation[id][2] + 1);

    for (int i = 0; i < 3; i++) {
        if (request[i] > available[i]) { // Check if the request can be granted
            printf("Request %d for resource %d cannot be granted\n", id, i);
            pthread_exit(NULL);
        }
    }

    for (int i = 0; i < 3; i++) {
        available[i] -= request[i];
        allocation[id][i] += request[i];
        need[id][i] = max[id][i] - allocation[id][i];
    }

    printf("Request %d for resources {%d, %d, %d} granted\n", id, request[0], request[1], request[2]);

    if (!is_safe()) {
        printf("Request %d caused an unsafe state\n", id);
    }

    for (int i = 0; i < 3; i++) {
        available[i] += request[i];
        allocation[id][i] -= request[i];
        need[id][i] = max[id][i] - allocation[id][i];
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[3];
    int ids[3] = { 0, 1, 2 };
    
    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, customer, &ids[i]);
    }
    
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}
