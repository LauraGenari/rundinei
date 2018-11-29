#ifndef AUXILIARES_H
#define AUXILIARES_H
#include <stdio.h>
#include "trie.h"

typedef struct Lista LISTA;
typedef struct Site SITE;

LISTA * le_csv(char * arquivo, Notrie* no);
void busca_keyword(Notrie* no,LISTA * lista);
void insereword_trie(Notrie* no,char ** keywords, int words, int id);
SITE* le_linha(FILE *fp, Notrie* no);
void Exibir_Site(LISTA* buffer);
void Remover_Site(LISTA * lista,Notrie* no);
void Atualizar_Relevancia(LISTA * lista);
void Inserir_Keyword(LISTA * lista);
void Sair(LISTA *buffer, char* nome);
void Inserir_Site(LISTA * lista, Notrie* no);
void inserir_novo_site(LISTA* lista, Notrie* no);
char ** vetor_palavras(int * nros, LISTA * l, int*site);
LIST_ENC** iniciar_bucked(int tam);
void bucked_inserir(int pos, LIST_ENC** bucked, int rel);
void bucked_remover(int pos, LIST_ENC** bucked, int rel);
LIST_ENC* tirar_bucked(LIST_ENC** bucked, int tam);
void liberar_bucked(LIST_ENC** bucked, int tam);
LIST_ENC** recomendados(int* nros, LISTA* lista, Notrie* no);

#endif
