#ifndef AUXILIARES_H
#define AUXILIARES_H
#include <stdio.h>
#include "trie.h"

typedef struct Lista LISTA;
typedef struct Site SITE;

LISTA * le_csv(char * arquivo, Notrie* no);
void busca_keyword(Notrie* no);
void insereword_trie(Notrie* no,char ** keywords, int words);
SITE* le_linha(FILE *fp, Notrie* no);
void Exibir_Site(LISTA* buffer);
void Remover_Site(LISTA * lista);
void Atualizar_Relevancia(LISTA * lista);
void Inserir_Keyword(LISTA * lista);
void Sair(LISTA *buffer, char* nome);
void Inserir_Site(LISTA * lista);
void inserir_novo_site(LISTA* lista);

#endif
