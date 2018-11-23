#include <stdio.h>
#include <stdlib.h>
#include "encadeia.h"

LIST_ENC* cria_lista(){
  LIST_ENC* lista = malloc(sizeof(LIST_ENC));
  lista->comeco = NULL;
  lista->fim = NULL;
  return lista;
}

NO* cria_no(int id){

}
void inserir(int id, LIST_ENC* lista){
  if (lista->comeco == NULL) {
    lista->comeco = cria_no(id);
    return;
  }else inserir_no(id, lista->comeco);
  return;
}

void inserir_no(int id, NO* no){
  if (no->proximo == NULL) {
    lista->comeco = cria_no(int id);
    return;
  }else inserir_no(id, lista->comeco);
  return;
}

void remover_no(int id, LIST_ENC* lista){
NO* aux1 = lista->comeco, aux2;
if (lista->comeco == NULL) {
  return;
}

if (lista->comeco->id == id) {
  lista->comeco = lista->comeco->proximo;
  free(aux1);
  return;
}

aux2 = lista->comeco->proximo;
while (aux2 != NULL) {
  if (aux2->id == id) {
    aux1->proximo = aux2->proximo;
    free(aux2);
    return;
  }
  aux1 = aux2;
  aux2 = aux2->proximo;
}

}

int* mostra_id(LIST_ENC* lista){

  return ler_ids();
}

int* ler_ids(){

}

void libera(LIST_ENC* lista){
  libera_no(lista->comeco);
  free(lista);
}

void libera_no(NO* no){
  if(no->proximo != NULL) {
    libera_no(no);
  }
  free(no);
}
