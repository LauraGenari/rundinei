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
	Notrie* ramos[35];
};

void tratapalavra(char* palavra, int* novapalavra);
void incluipalavra(Notrie* no, int* palavra, int id, int i);
int checapalavra(Notrie* no, int* palavra);
void limpaarvore(Notrie* no);