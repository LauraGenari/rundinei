#ifndef ENCADEIA_H
#define ENCADEIA_H
#include <stdio.h>
#include <stdlib.h>

typedef struct list_enc LIST_ENC;
typedef struct no NO;

struct list_enc {
	NO* inicio;
	NO* fim;
	int tam;
};

struct no{
 	NO* proximo;
	NO* anterior;
	int id;
};


LIST_ENC* cria_lista();
NO* cria_no(LIST_ENC* lista, int id);
void remover_no(LIST_ENC* lista, int id);
int* mostra_id(LIST_ENC* lista);
void libera(LIST_ENC* lista);
void libera_no(NO* no);
int achar_no(LIST_ENC* lista, int id);
int remove_first(LIST_ENC* lista);


#endif
