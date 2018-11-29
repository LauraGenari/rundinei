#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "site.h"
#include "lista.h"
#include "auxiliares.h"

//ate aqui mandar para achar no
LIST_ENC** iniciar_bucked(int tam){//ok
  LIST_ENC** lista = malloc(tam*sizeof(LIST_ENC));
  int i;
  for(i = 0; i < tam; i++){
  lista[i] = cria_lista();
  }
  return lista;
}

void bucked_inserir(int pos, LIST_ENC** bucked, int rel){//ok
  if (achar_no(bucked[rel], pos)) {
    cria_no(bucked[rel], pos);
  }
}

void bucked_remover(int pos, LIST_ENC** bucked, int rel){//ok
  if (achar_no(bucked[rel], pos) == 0) {
    remover_no(bucked[rel], pos);
  }
}

LIST_ENC* tirar_bucked(LIST_ENC** bucked, int tam){//ok
  //(*j) = 0;
  LIST_ENC* ordem = cria_lista();
  int i = tam - 1;
  int a;
  while(i >= 0){

    a = remove_first(bucked[i]);
    //(*j)++;
    while (a != -1) {
      cria_no(ordem, a);
      a = remove_first(bucked[i]);
      //(*j)++;
    }
    i--;
  }
  return ordem;
}

void liberar_bucked(LIST_ENC** bucked, int tam){//ok
  int i;
  for (i = 0; i < tam; i++) {
    libera(bucked[i]);
  }
  free(bucked);
}

int main(int argc, char const *argv[]) {
  LIST_ENC* lista = cria_lista();
  int a = 0;
  int b;
  int* j = malloc(sizeof(int));
  scanf("%d", &b);
  LIST_ENC** bucked = iniciar_bucked(1001);

  for (int i = 0; i < b; i++){
    scanf("%d", &a);
    cria_no(lista, a);
  }

  a = remove_first(lista);
  while (a != -1) {
    bucked_inserir(a, bucked, a);
    a = remove_first(lista);
  }
  libera(lista);


  //a = 14;//numero que vc remove;
  //bucked_remover(a, bucked, a);

  lista = tirar_bucked(bucked, 1001);
  a = remove_first(lista);
  while (a != -1) {
    printf("%d\n", a);
    a = remove_first(lista);
  }
  liberar_bucked(bucked, 1001);
  libera(lista);
  free(j);
  return 0;
}
