#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "site.h"
#include "lista.h"
#include "auxiliares.h"

LISTA * le_csv(char * arquivo, Notrie* no){
  FILE * fp = NULL;
  LISTA * buffer=NULL;
  SITE * aux=NULL;
  int tam = 100, i=0;

  fp = fopen(arquivo, "r");
	if(fp == NULL){
	    printf("\narquivo não encontrado\nexecute o programa e tente novamente:\n");
            free(no);
			return NULL;
	}

  buffer = criar_lista(tam);
	while(!feof(fp)){
		aux = le_linha(fp, no);
    if(aux == NULL) break;

    inserir_site_lista(buffer, aux);
	liberar_site(aux);

    if(buffer->fim >= tam - 2){
       tam += (tam/2);
       aumentar_lista(buffer, tam);
  	}

  }
  fclose(fp);
	return buffer;
}

SITE * le_linha(FILE *fp, Notrie* no){
	if (fp == NULL) return ERRO;

  SITE * aux;
  int aux_id, aux_rel, i = 0, verifica;
  char aux_nome[50], aux_link[100],** aux_keywords, *c, debug;

  c = (char*)malloc(50*sizeof(char));
  if (c == NULL) return ERRO;

  aux_keywords = (char**)malloc(10 * sizeof(char*));

  for(i = 0; i < 10; i++){
    aux_keywords[i] = (char*)malloc(50 * sizeof(char));

  }

	if(aux_keywords == NULL) return ERRO;

	 verifica = fscanf(fp, "%d%*c%[^,]%*c%d%*c%[^,]%c", &aux_id , aux_nome, &aux_rel, aux_link, &debug);
	 if(verifica == -1){
     fflush(fp);
     for(i = 0; i < 10; i++){
       free(aux_keywords[i]);
     }
    free(aux_keywords);
    free(c);

     return NULL;
   }

   int count = 0, words = 0;
	 fscanf(fp, "%c", &c[count]);
	 while(c[count] != '\n'){
   	if(c[count] == ','){
	 		c[count] = '\0';
	 		strcpy(aux_keywords[words], c);
	 		words++;
	 		count = 0;
	 		fscanf(fp,"%c", &c[count]);
	 		continue;
	 	}
 		count++;
 		fscanf(fp,"%c", &c[count]);
 	}
 	c[count] = '\0';

 	strcpy(aux_keywords[words], c);
 	words++;

    aux = criar_site(aux_id, aux_nome, aux_rel, aux_link, aux_keywords, words);
    insereword_trie(no, aux_keywords, words, aux_id);

    for(i = 0; i < 10; i++){
        free(aux_keywords[i]);
    }

    free(aux_keywords);

	free(c);


    return aux;
}

void insereword_trie(Notrie* no,char ** keywords, int words, int id){
    int i;
    for(i = 0; i < words; i++){
        incluipalavra(no, keywords[i], id);
    }
}

void busca_keyword(Notrie* no, LISTA* lista){
    char* palavra = malloc(50 * sizeof(char));
    int* pos;
    int* nros;

    printf("Digite uma palavra a ser buscada\n");
    scanf("%s", palavra);
    nros = checapalavra(no, palavra);
    if(nros == NULL){
    	printf("palavra nao encontrada\n");
    }
    else{
    	printf("achou:\n");
    	//int* pos = malloc(sizeof(int)*nros[0]);
    	for (int i = 0; i < nros[0]; ++i){
    		printf("%d\n", nros[i+1]);
    	}
    }

    //free(pos);
    free(nros);
    free(palavra);
}

void Remover_Site(LISTA * lista, Notrie * no){
  int seletor = 0, ID, verifica;

  while(seletor != 1){
    printf("Digite a opcao desejada\n1-Remover ID\n\n2-Voltar\n");
    verifica = scanf("%d", &seletor);
		if(verifica == -1){
      fflush(stdin);
    }
    if (seletor < 1 || seletor > 2) {
      printf("ERRO!!!!\nInsira um valor valido\n");
    }
		else if (seletor == 2) {
      return;
    }
  }
  remo_site(lista,no);
}

void Atualizar_Relevancia(LISTA * lista){
  int seletor = 0, ID, verifica;
  while(seletor != 1){
    printf("\nDigite a opção desejada\n1-Alterar a relevancia\n2-Voltar\n\n");
    verifica = scanf("%d", &seletor);
		if(verifica == -1){
      fflush(stdin);
    }
    if (seletor < 1 || seletor > 2) {
      printf("\nERRO!!!!\nInsira um valor valido\n\n");
    }
		else if (seletor == 2) {
      return;
    }
  }
  alt_rel(lista);
}

void Inserir_Keyword(LISTA * lista){
	  int seletor, verifica;
	  printf("\nDigite a opção desejada\n1-Adicionar palavra chave\n\n2-Voltar\n");
		while(seletor != 1){
			verifica = scanf("%d", &seletor);
			if(verifica == -1){
	      fflush(stdin);
				printf("\nERRO!!!!\ndigite a opcao correta (1 ou 2)\n");
	    	}else	if (seletor < 1 || seletor > 2) {
		    	printf("\nERRO!!!!\nInsira um valor valido (1 ou 2)\n\n");
		  	}
			else if (seletor == 2) {
		    return;
		  	}
			}
	   ins_palavra_chave(lista);
	}

void inserir_novo_site(LISTA* lista){
  SITE * aux;
  int aux_id, aux_rel, aux_nrowords = 0, i, verifica;
  char aux_link[100], aux_nome[50], c = 's',** aux_keywords;


  aux_keywords =(char **) malloc(10 * sizeof(char*));
  for(i = 0; i < 10; i++){
    aux_keywords[i] = (char *) malloc(50 * sizeof(char));
  }
	if(aux_keywords == NULL){

    for(i = 0; i < 10; i++){
      free(aux_keywords[i]);
    }

    free(aux_keywords);
    aux_keywords == NULL;
    return;
  }

  printf("\nEscreva as informações do novo site:\n\nID do novo site:\t");
  verifica = scanf("%d", &aux_id);

	int pos = busca_binaria(aux_id, lista);
  while(( pos != erro) || aux_id > 9999 || aux_id < 0 || verifica == -1){
    printf("\ninsira um ID valido:\t");
    scanf("%d", &aux_id);
		pos = busca_binaria(aux_id, lista);
  }

  printf("\nEscreva o nome do novo site:\t");
  verifica = scanf("%s", aux_nome);

  while(verifica == -1) {
		fflush(stdin);
		printf("ERRO!!!\nEscreva um nome de até 50 caracteres\n");
	}

  printf("\nEscreva a relevancia dele:\t");
  verifica = scanf("%d", &aux_rel);

  while(aux_rel > 1000 || aux_rel < 0){
    printf("\n%d insira uma relevancia valida (0 - 1000):\t", aux_rel);
    verifica = scanf("%d", &aux_rel);
  }

  printf("\nEscreva o URL do novo site: \t");
  verifica = scanf("%s", aux_link);

  while(c == 's' && aux_nrowords < 10){
		if(c != 'n'){
	    printf("\nEscreva a palavra chave do novo site: \t");
	    verifica = scanf("%s", aux_keywords[aux_nrowords]);
      int i = 0;
      while(aux_keywords[aux_nrowords][i]!= '\0'){
          int cast = aux_keywords[aux_nrowords][i];
          if(cast < 0){
            printf("\nA palavra possui caracter invalido. Insira novamente\n");
            i = -1;
            break;
          }
          i++;
      }

      if(i != -1){
    	    printf("\n voce deseja inserir nova palavra chave (s/n)\t");
    	    verifica = scanf(" %c", &c);
    			while (c != 's' && c != 'n') {
    	      printf("\n escreva uma resposta valida (s/n)\t");
    	      verifica = scanf(" %c", &c);
    	    }
          aux_nrowords++;
      }
    }
  }

	aux = criar_site(aux_id, aux_nome, aux_rel, aux_link, aux_keywords, aux_nrowords);
  inserir_site_lista(lista, aux);

	printf("\nSite adicionado com sucesso!\nPara descarregá-lo no arquivo, digite 6 e saia do programa\n");

  for(i = 0; i < 10; i++){
    free(aux_keywords[i]);
  }

  free(aux_keywords);
	free(aux);
}

void Sair(LISTA *buffer, char* nome){
  FILE *fp;
  fp = fopen(nome, "w");
	if (fp == NULL) return;
  printf("\nescrevendo arquivo....\n");
	descarrega_lista(buffer, fp);
  liberar_lista(buffer);
  printf(".\n.\n.\n.\n.\n.\n.\n saindo...\n");
	fclose(fp);
}

void Inserir_Site(LISTA * lista){
	if(lista == NULL) return;
  int seletor = 0, ID, verifica;
  while(seletor != 1){
    printf("\nDigite a opção desejada\n1-Inserir ID\n2-Voltar\n\n");
    verifica = scanf("%d", &seletor);
		if (verifica == -1) {
			fflush(stdin);
		}
    if (seletor < 1 || seletor > 2) {
      printf("\nERRO!!!!\nInsira um valor valido\n");
    }
		else if (seletor == 2) {
      return;
    }
  }
  inserir_novo_site(lista);
}
