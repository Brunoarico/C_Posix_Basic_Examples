#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NITER 1000000

int cnt = 0;

void* Count(void* a) {
    int i, tmp;
    for (i = 0; i < NITER; i++) {
        tmp = cnt;      /* copia cnt globalmente */
        tmp = tmp + 1;  /* incrementa a copia local */
        cnt = tmp;      /* armazena o valor local em cnt global */
    }
}

int main() {
    pthread_t tid1, tid2;

    //pthread_create(<identificador_da_thread>, <atributos_da_thread>, <funcao_da_thread>, <argumentos_da_thread>)
    if (pthread_create(&tid1, NULL, Count, NULL)) {
        printf("\n ERRO criacao da thread 1");
        exit(1);
    }

    if (pthread_create(&tid2, NULL, Count, NULL)) {
        printf("\n ERRO criacao da thread 2");
        exit(1);
    }

    //pthread_join(<identificador_da_thread>, <retorno_da_thread>)
    if (pthread_join(tid1, NULL)) { 
        printf("\n ERRO no joining da thread 1");
        exit(1);
    }

    if (pthread_join(tid2, NULL)) { 
        printf("\n ERRO no joining da thread 2");
        exit(1);
    }

    if (cnt < 2 * NITER)
        printf("\n Erro! cnt = [%d], mas deveria ser %d\n", cnt, 2 * NITER);
    else
        printf("\n OK! cnt = [%d]\n", cnt);
    
    pthread_exit(NULL);
}
