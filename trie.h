#ifndef TRIE_H
#define	TRIE_H
#include <stdio.h>
#include <stdlib.h>

typedef struct CHAINLIST Nolist;
struct CHAINLIST{
	int id;
	Nolist* prox;
};

typedef struct TRIE Notrie;
struct TRIE{
	Nolist* ids;
	int flag;
	Notrie* ramos[37];
};

void incluipalavra(Notrie* no, int* palavra, int id);
void tratapalavra(char* palavra, int* novapalavra);
int checapalavra(Notrie* no, int* palavra);
void limpaarvore(Notrie* no);

#endif