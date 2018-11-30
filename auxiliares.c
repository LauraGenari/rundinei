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
LIST_ENC** recomendados(int* nros, LISTA* lista, Notrie* no){
  int* nros1;
  int a, i = 0, j, size;
  LIST_ENC** bucked = iniciar_bucked(1001);
  char** string = vetor_palavras(nros, lista, &size);
  while(i < size){
    nros1 = checapalavra(no, string[i]);
    for (j = 0; j < nros1[0]; j++) {
      a = busca_binaria(nros1[j+1], lista);
      bucked_inserir(a, bucked, lista->site[a].rel);
    }
    free(nros1);
    i++;
  }
  for (i = 0; i < nros[0]; i++) {
    a = busca_binaria(nros[i+1], lista);
    bucked_remover(a, bucked, lista->site[a].rel);
  }
  for (i = 0; i < size; i++) {
    free(string[i]);
  }
  free(string);
  return bucked;
}

void busca_keyword(Notrie* no, LISTA* lista){
    char* palavra = malloc(50 * sizeof(char));
    int* pos;
    int* nros;
    LIST_ENC** bucked = iniciar_bucked(1001);
    int a, i;
    LIST_ENC* ordem;
    printf("Digite uma palavra a ser buscada\n");
    scanf("%s", palavra);
    nros = checapalavra(no, palavra);
    while(nros == NULL){
    	printf("\npalavra nao encontrada !!!\nescreva nova palavra para ser buscada:");
      scanf("%s", palavra);
      nros = checapalavra(no, palavra);
    }

      	for (i = 0; i < nros[0]; i++) {
        	a = busca_binaria(nros[i+1], lista);
        	bucked_inserir(a, bucked, lista->site[a].rel);
      	}

    	  ordem = tirar_bucked(bucked, 1001);
        a = remove_first(ordem);
        printf("\n");
        while(a != -1){
        	printf("%s %s\n", lista->site[a].nome, lista->site[a].link); //nao mexer no printf, na duvida ler o pdf!!!!
            a = remove_first(ordem);
          }
        printf("\n");
        /**/
        bucked = recomendados(nros, lista, no);
        ordem = tirar_bucked(bucked, 1001);
        a = remove_first(ordem);
        printf("\n");
        while(a != -1){
        	printf("%s %s\n", lista->site[a].nome, lista->site[a].link); //nao mexer no printf, na duvida ler o pdf!!!!
            a = remove_first(ordem);
          }
        printf("\n");

    libera(ordem);
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

void Inserir_Keyword(Notrie* no,LISTA * lista){
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

		
	   ins_palavra_chave(no,lista);
	}

void inserir_novo_site(LISTA* lista, Notrie* no){
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


  insereword_trie(no, aux_keywords, aux_nrowords, aux_id);
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

void Inserir_Site(LISTA * lista, Notrie* no){
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
  inserir_novo_site(lista,no);
}

char ** vetor_palavras(int * nros, LISTA * l, int * size){
  int i, j, k;
  char ** palavra = (char**)malloc(sizeof(char*)*131072);
   for (i = 0; i < 131072; i++) {
     palavra[i] = (char*)malloc(sizeof(char)*45);
   }
   for (i = 0; i < 131072; i++) {
     palavra[i][0] = '\0';
   }
   (*size)=0;
   for(i = 1; i <= nros[0]; i++) {
    int pos = busca_binaria(nros[i],l);
    (*size) += l->site[pos].nrowords;
    // printf("%d\n", size);
    for(j = 0; j < l->site[pos].nrowords; j++){
    //  printf("j= %d, %s\n",j, l->site[pos].keywords[j]);
      int strsize = strlen(l->site[pos].keywords[j]),potdedois=2,hash=0;
      for(k = 0; k < strsize; k++){
          hash += (int)l->site[pos].keywords[j][k]*potdedois;
          potdedois*=2;
      }
      if(palavra[hash&131071][0] == '\0') strcpy(palavra[hash&131071], l->site[pos].keywords[j]);
      else{
        int sond = 1;
        while (palavra[hash&131071][0] != '\0') {
          if(strcmp(palavra[hash&131071],l->site[pos].keywords[j])==0){
            (*size)--;
             break;
           }
            hash += (sond + sond*sond)/2;
         }
         strcpy(palavra[hash&131071], l->site[pos].keywords[j]);
      }
    }
  }

  char ** string = (char**)malloc(sizeof(char*)*(*size));
   for (i = 0; i < (*size); i++) {
     string[i] = (char*)malloc(sizeof(char)*45);
   }
  j = 0;
  for (int i = 0; i <  131072; i++) {
    //printf("%s\n", palavra[i]);
    if(palavra[i][0] != '\0') {
      strcpy(string[j], palavra[i]);
      //printf("%s\n", string[j]);
      j++;
    }
  }
  // printf("%d\n", (*size));
  // for(j=0; j< (*size); j++){
  //   printf("%d %s\n",j, string[j]);
  // }


  for (i = 0; i < 131072; i++) {
    free(palavra[i]);
  }
  free(palavra);
  return string;
}

 LIST_ENC** iniciar_bucked(int tam){//ok
   LIST_ENC** lista = malloc(tam*sizeof(LIST_ENC));
   int i;
   for(i = 0; i < tam; i++){
   lista[i] = cria_lista();
   }
   return lista;
 }

 void bucked_inserir(int pos, LIST_ENC** bucked, int rel){//ok
   	if (achar_no(bucked[rel], pos)){
     	cria_no(bucked[rel], pos);
   	}
 }

 void bucked_remover(int pos, LIST_ENC** bucked, int rel){//ok
   if (achar_no(bucked[rel], pos) == 0) {
     remover_no(bucked[rel], pos);
   }
 }

 LIST_ENC* tirar_bucked(LIST_ENC** bucked, int tam){//ok
   LIST_ENC* ordem = cria_lista();
   int i = tam - 1;
   int a;
   while(i >= 0){

     a = remove_first(bucked[i]);
     while (a != -1) {
       cria_no(ordem, a);
       a = remove_first(bucked[i]);
     }
     i--;
   }
   liberar_bucked(bucked, tam);
   return ordem;
 }

 void liberar_bucked(LIST_ENC** bucked, int tam){//ok
   int i;
   for (i = 0; i < tam; i++) {
     libera(bucked[i]);
   }
   free(bucked);
 }
