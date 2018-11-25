#ifndef TRIE_H
#define	TRIE_H
#include <stdio.h>
#include <stdlib.h>
#include "encadeia.h"

typedef struct TRIE Notrie;
struct TRIE{
	LIST_ENC* lista;
	Notrie* ramos[37];
};

void incluipalavra(Notrie* no, int* palavra, int id);
void tratapalavra(char* palavra, int* novapalavra);
int* checapalavra(Notrie* no, int* palavra);
void limpaarvore(Notrie* no);

#endif