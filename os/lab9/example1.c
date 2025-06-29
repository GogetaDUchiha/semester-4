#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t semVar;

void *sem_func(void *arg) {
    sem_wait(&semVar);
    printf("Entered\n");

    // Critical section
    sleep(2);

    printf("Just Exiting\n");
    sem_post(&semVar);
    pthread_exit(NULL);
}

int main() {
    pthread_t tid1, tid2;

    sem_init(&semVar, 0, 1);

    pthread_create(&tid1, NULL, sem_func, NULL);
    // sleep(1); // Optional: Uncomment to add delay between thread creation
    pthread_create(&tid2, NULL, sem_func, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("Out of thread\n");

    sem_destroy(&semVar);

    return 0;
}
