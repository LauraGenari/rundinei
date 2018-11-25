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
			if(no->ids == NULL){
				//no->ids = cria_lista();
				//no->flag = 1;
				no->ids = (Nolist*)0x82133;
				return;
			}
			else{
				//inserir(id, no->ids);
				//no->flag = 1;
				no->ids = (Nolist*)0x82133;
				return;
			}
		}
		Notrie* novono;
		if(no->ramos[palavra[i]] != NULL){//caso o no ja aponte para um novono, o novono recebe o end ja existente
			novono = no->ramos[palavra[i]];
		}
		else{//caso contrario, cria o novono
			novono = malloc(sizeof(Notrie));
			if(novono == NULL){
				printf("malloc não foi feito");	
				return;
			}
			no->ramos[palavra[i]] = novono;
		}
		no = novono;
		i++;
	}
}

int checapalavra(Notrie* no, int* palavra){
	int i = 0;
	while(1){
		if(palavra[i] == -1){
			if(no->ids != NULL) return 1;
			else return 0;
		}
		if(no->ramos[palavra[i]] == NULL){return 0;}//caso um nó não tenha um ponteiro para a próxima letra, retorna 0
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
	//liberalistaencadeada();
	free(no);	
}

/*int main(){
	clock_t time1 = clock();
	clock_t time2 = clock();
	time1 = clock();
	time2 = clock();
	//printf("tmpo: %ld\n", time2 - time1);
	char* palavra = malloc(300 * sizeof(char));
	int* palavranova = malloc(300 * sizeof(int));
	int i = 0;
	int flag = 0;
	int controle;
	Notrie* no = malloc(sizeof(Notrie)); 
	scanf("%d", &controle);
	while (controle != 10){
		if(controle == 1){
			scanf("%s", palavra);
			tratapalavra(palavra, palavranova);
			incluipalavra(no, palavranova, 3);
		}
		else{
			scanf("%s", palavra);	
			tratapalavra(palavra, palavranova);
			time1 = clock();
			flag = checapalavra(no, palavranova);
			time2 = clock();
			printf("tmpo: %ld\n", time2 - time1);
			if(flag)printf("achou? sim\n");
			else printf("achou? não\n");
		}
		scanf("%d", &controle);
	}

	limpaarvore(no);
	free(palavra);
	free(palavranova);
}



// 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36
// 0 1 2 3 4 5 6 7 8 9 a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z  ' ' */



