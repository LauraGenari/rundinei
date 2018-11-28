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

void incluipalavra(Notrie* no, char* palavrachar, int id);
int* tratapalavra(char* palavra);
int* checapalavra(Notrie* no, char* palavrachar);
void removepalavra(Notrie* no, char* palavrachar, int id);
void limpaarvore(Notrie* no);

#endif