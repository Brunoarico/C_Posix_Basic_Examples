#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Este sistema é compatível com POSIX. Versão: %ld\n", _POSIX_VERSION);
    return 0;
}