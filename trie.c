#include <time.h>
#include "trie.h"

void tratapalavra(char* palavra, int* novapalavra){
	int i = 0;
	while(palavra[i] != '\0'){
		if(palavra[i] > 47 && palavra[i] < 58){
			novapalavra[i] = palavra[i] - 48;
		}
		else if(palavra[i] > 96 && palavra[i] < 123){
			novapalavra[i] = palavra[i] - 87;
		}
		else if(palavra[i] > 64 && palavra[i] < 91){
			novapalavra[i] = palavra[i] - 55;
		}
		else if(palavra[i] == ' '){
			novapalavra[i] = 36;
		}
		else{
			printf("c invalido");
		}
		i++;
	}
	novapalavra[i] = -1;
}


void incluipalavra(Notrie* no, int* palavra, int id){
	int i = 0;
	while(1){
		if(palavra[i] == -1){ 
			if(no->lista == NULL){
				no->lista = cria_lista();
				cria_no(no->lista, id);
				return;
			}
			else{
				cria_no(no->lista, id);
				return;
			}
		}
		Notrie* novono;
		if(no->ramos[palavra[i]] != NULL){//caso o no ja aponte para um novono, o novono recebe o end ja existente
			novono = no->ramos[palavra[i]];
		}
		else{//caso contrario, cria o novono
			novono = malloc(sizeof(Notrie));
			novono->lista = NULL;
			no->ramos[palavra[i]] = novono;
		}
		no = novono;
		i++;
	}
}

int* checapalavra(Notrie* no, int* palavra){
	int i = 0;
	while(1){
		if(palavra[i] == -1){
			if(no->lista != NULL){
				int* vet = mostra_id(no->lista);
				return vet;
			}
			else return NULL;
		}
		if(no->ramos[palavra[i]] == NULL){return NULL;}//caso um nó não tenha um ponteiro para a próxima letra, retorna 0
		no = no->ramos[palavra[i]];
		i++;
	}
}

void removepalavra(Notrie* no, int* palavra, int id){
	int i = 0;
	while(1){
		if(palavra[i] == -1){
			if(no->lista != NULL){
				remover_no(no->lista, id);
				return;
			}
			else return;
		}
		if(no->ramos[palavra[i]] == NULL){return;}//caso um nó não tenha um ponteiro para a próxima letra, retorna 0
		no = no->ramos[palavra[i]];
		i++;
	}
}

void limpaarvore(Notrie* no){
	for(int i = 0; i < 37; i++){
		if(no->ramos[i] != NULL){	
		limpaarvore(no->ramos[i]);
		}
	}
	if(no->lista != NULL)
		libera(no->lista);
	free(no);	
}
/*
int main(){
	clock_t time1 = clock();
	clock_t time2 = clock();
	time1 = clock();
	time2 = clock();
	//printf("tmpo: %ld\n", time2 - time1);
	char* palavra = malloc(300 * sizeof(char));
	int* palavranova = malloc(300 * sizeof(int));
	int* nros;
	int i = 0;
	int id;
	int controle;
	Notrie* no = malloc(sizeof(Notrie)); 
	scanf("%d", &controle);
	while (controle != 10){
		if(controle == 1){
			printf("insira o id\n");
			scanf("%d", &id);
			printf("agr a palavra\n");
			scanf("%s", palavra);
			tratapalavra(palavra, palavranova);
			incluipalavra(no, palavranova, id);
		}
		else if(controle == 3){
			printf("insira o id\n");
			scanf("%d", &id);
			printf("agr a palavra\n");
			scanf("%s", palavra);
			tratapalavra(palavra, palavranova);
			removepalavra(no, palavranova, id);
		}
		else{
			scanf("%s", palavra);	
			tratapalavra(palavra, palavranova);
			time1 = clock();
			nros = checapalavra(no, palavranova);
			time2 = clock();
			printf("tmpo: %ld\n", time2 - time1);
			if(nros == NULL)
				printf("achou? nao\n");
			else{
				printf("achou? sim, nros:\n");
				for (int i = 1; i < nros[0]; ++i)
				{
					printf("nros[%d] = %d\n", i-1,nros[i]);
				}
				free(nros);
			}
		}
		scanf("%d", &controle);
	}

	limpaarvore(no);
	free(palavra);
	free(palavranova);
}



// 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36
// 0 1 2 3 4 5 6 7 8 9 a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z  ' ' */



