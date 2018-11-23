#ifndef "encadeia_h"
#include <stdio.h>
#include <stdlib.h>

typedef struct list_enc LIST_ENC;
typedef struct  no NO;

struct list_enc {
  NO* comeco;
  NO* fim
};

struct no{
  no* proximo;
  no* anterior;
  int id;
};


LIST_ENC* cria_lista();
void inserir(int id, LIST_ENC* lista);
void inserir_no(int id, NO* no);
void remover_no(int id, LIST_ENC* lista);
int* mostra_id(LIST_ENC* lista);
int* ler_ids();
void libera(LIST_ENC* lista);
void libera_no(NO* no);
NO* cria_no(int id);
#endif
