CC = gcc
CFLAGS = -Wall -Wextra -g 

all: qualFilme

qualFilme: qualFilme.c trie.c padronizaString.c 
	$(CC) $(CFLAGS) qualFilme.c trie.c padronizaString.c -o qualFilme

clean:
	-rm -f *.o 

purge: clean
	-rm -f qualFilme
	-rm -f *.swp
