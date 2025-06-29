#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_TICKETS 4
#define NUM_SELLERS 2

int numTickets = NUM_TICKETS;
pthread_mutex_t lock;

void *seller(void *arg) {
    int id = *(int *)arg;
    int mySales = 0;

    while (1) {
        pthread_mutex_lock(&lock);

        if (numTickets > 0) {
            numTickets--;
            mySales++;
            printf("Seller #%d sold one (%d left)\n", id, numTickets);
            pthread_mutex_unlock(&lock);
            sleep(1); // Simulate time taken to sell
        } else {
            pthread_mutex_unlock(&lock);
            break;
        }
    }

    printf("Seller #%d noticed all tickets sold! (I sold %d myself)\n", id, mySales);
    pthread_exit(NULL);
}

int main() {
    pthread_t sellers[NUM_SELLERS];
    int ids[NUM_SELLERS];

    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < NUM_SELLERS; i++) {
        ids[i] = i;
        pthread_create(&sellers[i], NULL, seller, &ids[i]);
    }

    for (int i = 0; i < NUM_SELLERS; i++) {
        pthread_join(sellers[i], NULL);
    }

    pthread_mutex_destroy(&lock);
    printf("Done\n");

    return 0;
}
