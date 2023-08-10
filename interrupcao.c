#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void alarm_handler(int signum) {
    printf("Temporizador expirou! Acao executada.\n");
    exit(0);
}

int main() {
    // Configurar o tratador de sinal para SIGALRM
    struct sigaction sa;
    sa.sa_handler = alarm_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGALRM, &sa, NULL) == -1) {
        perror("Erro ao configurar o tratador de sinal");
        return 1;
    }

    alarm(5); // Definir um temporizador para 5 segundos
    printf("Aguardando a expiracao do temporizador...\n");

    while (1) {
        // Aguardar indefinidamente ate que o sinal SIGALRM seja recebido
    }

    return 0;
}
