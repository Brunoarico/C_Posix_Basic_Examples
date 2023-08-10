CC = gcc
CFLAGS = -Wall -Wextra -pedantic
PFLAGS = -lpthread

all: interrupcao sincronizacao race mutex

interrupcao: interrupcao.c
	$(CC) $(CFLAGS) -o interrupcao interrupcao.c

sincronizacao: sincronizacao.c
	$(CC) $(CFLAGS) $(PFLAGS) -o sincronizacao sincronizacao.c

race: race.c
	$(CC) $(CFLAGS) $(PFLAGS) -o race race.c

mutex: mutex.c
	$(CC) $(CFLAGS) $(PFLAGS) -o mutex mutex.c

clean:
	rm -f interrupcao sincronizacao mutex race