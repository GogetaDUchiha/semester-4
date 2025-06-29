#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAXITEMS 5
#define BufferSize 5

sem_t empty;
sem_t full;
pthread_mutex_t lock;

int buffer[BufferSize];
int in = 0;
int out = 0;

void *producer(void *arg) {
    for (int i = 0; i < MAXITEMS; i++) {
        int item = rand();  // produce item

        sem_wait(&empty);
        pthread_mutex_lock(&lock);

        buffer[in] = item;
        printf("Produce Item: %d\n", buffer[in]);
        in = (in + 1) % BufferSize;

        pthread_mutex_unlock(&lock);
        sem_post(&full);

        sleep(1); // optional delay
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    for (int i = 0; i < MAXITEMS; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&lock);

        int item = buffer[out];
        printf("Remove Item: %d\n", item);
        out = (out + 1) % BufferSize;

        pthread_mutex_unlock(&lock);
        sem_post(&empty);

        sleep(1); // optional delay
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t tid1, tid2;

    sem_init(&empty, 0, BufferSize);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&lock, NULL);

    pthread_create(&tid1, NULL, producer, NULL);
    pthread_create(&tid2, NULL, consumer, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("Out of threads\n");

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&lock);

    return 0;
}
