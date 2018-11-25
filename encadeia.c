#include "encadeia.h"

LIST_ENC* cria_lista(){
  LIST_ENC* lista = malloc(sizeof(LIST_ENC));
  lista->inicio = NULL;
  lista->fim = NULL;
  lista->tam = 0;
  return lista;
}

NO* cria_no(LIST_ENC* lista, int id){
    NO* no = malloc(sizeof(NO));
    if(lista->tam == 0){
        no->anterior = NULL;
        lista->inicio = no; 
    }
    else{
        lista->fim->proximo = no;
        no->anterior = lista->fim;
    }
    lista->fim = no;
    no->proximo = NULL;
    no->id = id;
    lista->tam++;
}

void remover_no(LIST_ENC* lista, int id){
    NO* aux1 = lista->inicio, *aux2;
    if (lista->tam == 0) return;

    if(lista->inicio->id == id) {
        lista->inicio = lista->inicio->proximo;
        free(aux1);
        lista->tam--;
        return;
    }

    aux2 = lista->inicio->proximo;
    while (aux2 != NULL) {
      if (aux2->id == id) {
        aux1->proximo = aux2->proximo;
        free(aux2);
        lista->tam--;
        return;
      }
      aux1 = aux2;
      aux2 = aux2->proximo;
    }

}

void libera(LIST_ENC* lista){
  libera_no(lista->inicio);
  free(lista);
}

void libera_no(NO* no){
  if(no->proximo != NULL) {
    libera_no(no->proximo);
  }
  free(no);
}

int* mostra_id(LIST_ENC* lista){
    int* ids = malloc(sizeof(int) *(lista->tam + 1));   
    ids[0] = lista->tam + 1;
    NO* aux = lista->inicio;
    int i = 1;
    while(1){
        if(aux == NULL) break;
        ids[i] = aux->id;
        aux = aux->proximo;
        i++;
    }
    return ids;
}

int main(){
    LIST_ENC* lista = cria_lista();
    for (int i = 0; i < 10000; ++i)
    {
        cria_no(lista, i);
    }

    remover_no(lista, 9997);
    remover_no(lista, 9996);
    remover_no(lista, 9995);
    int* vet = mostra_id(lista);
    for (int i = 1; i < vet[0]; ++i){
        printf("%d\n", vet[i]);
    }

    free(vet);
    libera(lista);
}
/*
void inserir(SITE site, LIST_ENC* lista){
  if (lista->inicio == NULL) {
    lista->inicio = cria_no(id);
    return;
  }else inserir_no(id, lista->inicio);
  return;
}

void inserir_no(int id, NO* no){
  if (no->proximo == NULL) {
    lista->inicio = cria_no(int id);
    return;
  }else inserir_no(id, lista->inicio);
  return;
}*/
