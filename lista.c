#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "site.h"

int busca_binaria(int chave, LISTA* lista){
	int inf = 0;
	int sup = lista->fim;
	if(lista == NULL){
		printf("erro\n");
		return erro;
	}
	int media = (int)(inf+sup)/2.0;
	while(chave != lista->site[media].id && inf<sup){
		if(chave < lista->site[media].id){
			sup = media-1;
		}
		else if(chave > lista->site[media].id){
			inf = media+1;
		}
		media = (int)(inf+sup)/2.0;
  	}
  	if(chave == lista->site[media].id){
  		return media;
  	}
		return erro;
}

int busca_binaria_insercao(int chave, LISTA* lista){
	int inf = 0, sup = lista->fim;
	if(sup == 0 || lista->site[0].id > chave) return -1;
	if(lista == NULL){
		printf("erro\n");
		return erro;
	}

	while(sup-inf > 1){
		int media = (inf + sup)/2;
		if(lista->site[media].id > chave){
			sup = media;
		}
		else if(lista->site[media].id < chave){
			inf = media;
		}
		else if(lista->site[media].id == chave){
			if (lista->site[media].nome[0] != '\0') {
				return media;
			}
			else{
				printf("id já existente\n");
				return erro;
			}
		}
	}

	return inf;
}

void inserir_site_lista(LISTA * l, SITE * s){
		if(l == NULL || s == NULL) return;
		int pos = busca_binaria(s->id, l);
		if(pos != erro && l->site[pos].nome[0] == '\0'){
			copia_site(&(l->site[pos]), s);
			return;
		}
		pos = busca_binaria_insercao(s->id, l)+1;
		if(l->tam == l->fim){
			printf("Lista cheia\n");
			return;
		}
		else{
			int count = l->fim;
			l->fim++;
			while(count >= pos){
				copia_site(&(l->site[count+1]), &(l->site[count]));
				count--;
			}
			copia_site(&(l->site[pos]), s);
		}
}

LISTA * criar_lista(int tam){
	LISTA * l = malloc(sizeof(LISTA));
	l->tam = tam;
	l->site = (SITE*)malloc(tam*sizeof(SITE));
	l->fim = 0;
	if(l == NULL || l->site == NULL){
		printf("erro\n");
	}
	return l;
}

void liberar_lista(LISTA * l1){
  if(l1!=NULL){
    liberar_site(l1->site);
  	free(l1);
  }
  else{
    printf("ERRO\n");
  }
}

void aumentar_lista(LISTA * l1,int tam){
  if(l1!=NULL){
    l1=(LISTA*)realloc(l1, tam*sizeof(LISTA));
    if(l1 == NULL){
      printf("ERRO\n");
    }
  }
  else{
    printf("lista nao existente\n");
  }
}

int lista_cheia(LISTA * lista){
	if (lista == NULL) return erro;
  if(lista->fim + 1 == lista->tam){
    return 1;
  }
  return 0;
}

void descarrega_lista(LISTA * lista, FILE * fp){
	if(lista == NULL || fp == NULL) return;
  int count = 0;
  while(count < lista->fim){
			if(lista->site[count].nome[0] == '\0'){
				count++;
				continue;
			}
			descarregar_site(fp, &(lista->site[count]));
	    count++;
  }
}

void alt_rel(LISTA * lista){
	if(lista == NULL) return ;
	int ID;
	int r;
	int verifica;
	printf("Insira o ID:\n");
	verifica = scanf("%d", &ID);
	int pos = busca_binaria(ID, lista);
	while(pos == erro || ID > 9999 || ID < 0 || verifica == -1){
		fflush(stdin);
		printf("insira um ID valido:\n");
		verifica = scanf("%d", &ID);
		pos = busca_binaria(ID, lista);
	}
	printf("ID valida, insira a nova relevancia de %s\n", lista->site[pos].nome);
	verifica = scanf("%d", &r);
	while(r < 0 || r > 1000 || verifica == -1){
			fflush(stdin);
			printf("insira uma relevancia de 0 a 1000:\n");
			verifica = scanf("%d", &r);
	}
	alterar_relevancia(&(lista->site[pos]), r);
}

void remo_site(LISTA * lista){
	if (lista == NULL) return;
	char s[1];
	int ID;
	int verifica;
	printf("Insira o ID:\n");
	verifica = scanf("%d", &ID);
	int pos = busca_binaria(ID, lista);
	while(pos == erro || verifica == -1){
		printf("insira um ID valido:\n");
		verifica = scanf("%d", &ID);
		pos = busca_binaria(ID, lista);
	}

	printf("Tem certeza que deseja deletar o site %s? s/n\n", lista->site[pos].nome);
	scanf("%s", s);
	while(s[0] != 's' && s[0] != 'n'){
		printf("digite s ou n\n");
		scanf("%c", s);
	}
	if (s[0] == 's') {
	remover_site(&(lista->site[pos]));
	}
	else return;
}

void ins_palavra_chave(LISTA * lista){
	if(lista == NULL) return;
	char c[1];
	char palavra[50];
	int ID, verifica;
	printf("Insira o ID:\n");
	verifica = scanf("%d", &ID);
	int pos = busca_binaria(ID, lista);
	while(pos == erro || verifica == -1){
		fflush(stdin);
		printf("insira um ID valido:\n");
		verifica = scanf("%d", &ID);
		pos = busca_binaria(ID, lista);
	}

	printf("Digite a palavra-chave a ser adicionada:\n");
	scanf("%s", palavra);
	inserir_keyword(&(lista->site[pos]), palavra);
	printf("Voce deseja uma adicionar uma nova palavra chave? s/n\n");
	scanf("%s", c);
	while(c[0] != 's' && c[0] != 'n'){
		printf("Opcao invalida, digite s ou n\n");
		scanf(" %s", c);
	}
	if (c[0] == 's') {
	ins_palavra_chave(lista);
	}
	else return;
}
