#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

char word[] = "sistema de tempo real";
int wordLength = sizeof(word) - 1;

void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

void generatePermutations(int start) {
    if (start == wordLength - 1) {
        printf("%s\n", word);
        sleep(1);
        return;
    }
    for (int i = start; i < wordLength; ++i) {
        swap(&word[start], &word[i]);
        generatePermutations(start + 1);
        swap(&word[start], &word[i]);
    }
}

void handleAlarm() {
    printf("Geracao de permutacoes interrompida.\n");
    //alarm(<segundos>)
    alarm(2);
}

int main() {
    //signal(<sinal>, <tratador de sinal>)
    signal(SIGALRM, handleAlarm);  //Tratador de sinal para SIGALRM
    alarm(2);                      //Configurando o alarme para ocorrer em 2 segundos
    generatePermutations(0);
    printf("Fim\n");
    return 0;
}
