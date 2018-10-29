#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "site.h"

SITE * criar_site(int id, char * nome, int relevancia, char * link, char** keywords, int nrowords){
  SITE * s = (SITE*)malloc(sizeof(SITE));
  if(s!=NULL){
    s->id = id;
    strcpy(s->nome,nome);
    s->rel = relevancia;
    strcpy(s->link, link);
    s->nrowords = nrowords;

    int i;
    for (i = 0; i < nrowords; i++) {
      strcpy(s->keywords[i], keywords[i]);
    }
    return s;
  }
  else{
    printf("não foi possível criar um novo site\n");
    return ERRO;
  }
}

void copia_site(SITE * s1, SITE * s2){
  if(s1 != NULL && s2 != NULL){

    s1->id = s2->id;
    s1->rel = s2->rel;
    strcpy(s1->nome,s2->nome);
    strcpy(s1->link,s2->link);
    s1->nrowords = s2->nrowords;

    int i=0;
    for(i = 0; i < s2->nrowords; i++){
      strcpy(s1->keywords[i],s2->keywords[i]);
    }

  }
  else{
    printf("site(s) não existe(m)\n");
  }
}

void alterar_relevancia(SITE * s, int relevancia){
  if(s!=NULL){
    s->rel = relevancia;
  }
  else{
    printf("não foi possível alterar a relevancia\n");
  }
}

void remover_site(SITE * s){
  if(s!=NULL){
      s->nome[0]='\0';
  }
  else{
    printf("site não existe\n");
  }
}

void inserir_keyword(SITE * s, char * keyword){
  if(s!=NULL){
    if(s->nrowords <10){
      strcpy(s->keywords[s->nrowords], keyword);
      s->nrowords++;
    }
    else{
      printf("numero maximo de palavras atingido\n");
    }
  }
  else{
    printf("site não existe\n");
  }
}

void descarregar_site(FILE * arq, SITE * s){
  if(s!=NULL){
    if(arq != NULL){
      fprintf(arq, "%04d,%s,%04d,%s", s->id, s->nome, s->rel, s->link);
        int i;
        for (i= 0; i < s->nrowords; i++){
          fprintf(arq, ",%s", s->keywords[i]);
        }
      fprintf(arq, "\n");
    }
    else{
      printf("arquivo nao existe\n");
    }
  }
  else{
    printf("site não existe\n");
  }
}

void liberar_site(SITE * s){
  if(s!=NULL){
    free(s);
  }
  else{
    printf("site não existe\n");
  }
}
