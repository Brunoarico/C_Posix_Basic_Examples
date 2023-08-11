#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void alarm_handler(int signum) {
    printf("Temporizador expirou! Acao executada.\n");
    exit(0);
}

int main() {
    
    struct sigaction sa; // Configura o tratador de sinal para SIGALRM
    sa.sa_handler = alarm_handler;  // atribui o endereço da funcaoo alarm_handler a variavel sa.sa_handler

    sigemptyset(&sa.sa_mask);  // limpa o conjunto de sinais que sera bloqueado (mascarado) durante a execucao do tratador de sinal
    sa.sa_flags = 0; // reseta as flags de sinalizacao

    //sigaction(<sinal>, <tratador de sinal>, <old_actions>)
    if (sigaction(SIGALRM, &sa, NULL) == -1) { // Associa o tratador de sinal a SIGALRM
        perror("Erro ao configurar o tratador de sinal");
        return 1;
    }

    alarm(5);  // Definir um temporizador para 5 segundos, onde sera disparado o sinal SIGALRM
    printf("Aguardando a expiracao do temporizador...\n");

    while (1) {
    }  // Aguardar indefinidamente ate que o sinal SIGALRM seja recebido

    return 0;
}
