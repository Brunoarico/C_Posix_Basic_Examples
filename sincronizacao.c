#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 5  // tamanho do buffer
#define NUM_ITEMS 10   // numero de itens a serem produzidos/consumidos

int buffer[BUFFER_SIZE];
int buffer_index = 0;
sem_t empty, full;

void *producer(void *arg) {
    for (int i = 0; i < NUM_ITEMS; ++i) {
        int item = rand() % 100;
        sem_wait(&empty);  // Espera por um espaço vazio no buffer
        buffer[buffer_index++] = item;
        printf("Produzido: %d\n", item);
        sem_post(&full);  // Incrementa o contador de itens no buffer
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 0; i < NUM_ITEMS; ++i) {
        sem_wait(&full);  // Espera por um item no buffer
        int item = buffer[--buffer_index];
        printf("Consumido: %d\n", item);
        sem_post(&empty);  // Incrementa o contador de espaços vazios no buffer
    }
    return NULL;
}

int main() {
    sem_init(&empty, 0, BUFFER_SIZE); // Inicializa o semaforo empty com o valor BUFFER_SIZE
    sem_init(&full, 0, 0);           // Inicializa o semaforo full com o valor 0

    pthread_t producer_thread, consumer_thread;

    if (pthread_create(&producer_thread, NULL, producer, NULL)) exit(1);
    if (pthread_create(&consumer_thread, NULL, consumer, NULL)) exit(1);

    if (pthread_join(producer_thread, NULL)) exit(1);
    if (pthread_join(consumer_thread, NULL)) exit(1);

    sem_destroy(&empty); // Destroi o semaforo empty
    sem_destroy(&full); // Destroi o semaforo full

    return 0;
}
