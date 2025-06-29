#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t semVar;
int sharedVar = 0;

void *sem_func_1(void *arg);
void *sem_func_2(void *arg);

int main() {
    pthread_t tid1, tid2;

    sem_init(&semVar, 0, 1);

    pthread_create(&tid1, NULL, sem_func_1, NULL); // Increment
    pthread_create(&tid2, NULL, sem_func_2, NULL); // Decrement

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("Out of thread\n");

    sem_destroy(&semVar);

    return 0;
}

void *sem_func_1(void *arg) {
    int x;

    sem_wait(&semVar);

    x = sharedVar;
    x++;
    sharedVar = x;

    printf("Variable after increment (func_1): %d\n", sharedVar);

    sem_post(&semVar);

    pthread_exit(NULL);
}

void *sem_func_2(void *arg) {
    int x;

    sem_wait(&semVar);

    x = sharedVar;
    x--;
    sharedVar = x;

    printf("Variable after decrement (func_2): %d\n", sharedVar);

    sem_post(&semVar);

    pthread_exit(NULL);
}
