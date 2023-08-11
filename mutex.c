#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NITER 1000000

int cnt = 0;
pthread_mutex_t mutex;

void* Count(void* a) {
    int i, tmp;
    for (i = 0; i < NITER; i++) {
        pthread_mutex_lock(&mutex);    // bloqueia o mutex antes de acessar cnt
        tmp = cnt;                     // copia cnt globalmente
        tmp = tmp + 1;                 // incrementa a copia local
        cnt = tmp;                     // armazena o valor local em cnt global
        pthread_mutex_unlock(&mutex);  // libera o mutex após modificar cnt
    }
    return NULL;
}

int main() {
    pthread_t tid1, tid2;

    pthread_mutex_init(&mutex, NULL);  // inicia a estrutura do mutex

    if (pthread_create(&tid1, NULL, Count, NULL)) {  // instancia a thread 1
        printf("\n ERRO criacao da thread 1");
        exit(1);
    }

    if (pthread_create(&tid2, NULL, Count, NULL)) {  // instancia a thread 2
        printf("\n ERRO criacao da thread 2");
        exit(1);
    }

    if (pthread_join(tid1, NULL)) {  // espera a thread 1 terminar
        printf("\n ERRO no joining da thread 1");
        exit(1);
    }

    if (pthread_join(tid2, NULL)) {  // espera a thread 2 terminar
        printf("\n ERRO no joining da thread 2");
        exit(1);
    }

    pthread_mutex_destroy(&mutex);  // destroi a estrutura do mutex

    if (cnt < 2 * NITER)
        printf("\n Erro! cnt = [%d], mas deveria ser %d\n", cnt, 2 * NITER);
    else
        printf("\n OK! cnt = [%d]\n", cnt);

    pthread_exit(NULL);  // termina a thread principal
}
