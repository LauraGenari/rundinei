#ifndef LISTA_H
#define LISTA_H
#include "site.h"

typedef struct Lista{
	SITE * site;
	int tam;
	int fim;
} LISTA;

LISTA* criar_lista(int tam);
void inserir_site_lista(LISTA* lista, SITE * site);
int busca_binaria(int chave, LISTA* lista);
int busca_binaria_insercao(int chave, LISTA* lista);
void liberar_lista(LISTA * l1);
void aumentar_lista(LISTA * l1,int tam);
int lista_cheia(LISTA * lista);
void descarrega_lista(LISTA * lista, FILE * fp);
void alt_rel(LISTA* lista);
void remo_site(LISTA* lista);
void ins_palavra_chave(LISTA* lista);

#endif
