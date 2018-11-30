#include <time.h>
#include "trie.h"

int* tratapalavra(char* palavra){
	int* novapalavra = malloc(50*sizeof(int));
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
	return novapalavra;
}


void incluipalavra(Notrie* no, char* palavrachar, int id){
	//printf("asdasdasda");
	int* palavra = tratapalavra(palavrachar);
	int i = 0;

	while(1){
		if(palavra[i] == -1){ 
			if(no->lista == NULL){
				no->lista = cria_lista();
				cria_no(no->lista, id);
				free(palavra);
				return;
			}
			else{
				cria_no(no->lista, id);
				free(palavra);
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
	free(palavra);
}

int* checapalavra(Notrie* no, char* palavrachar){
	int* palavra = tratapalavra(palavrachar);
	int i = 0;
	while(1){
		if(palavra[i] == -1){
			if(no->lista != NULL){
				int* vet = mostra_id(no->lista);
				free(palavra);
				return vet;
			}
			else{
				free(palavra);
				return NULL;
			}
		}
		if(no->ramos[palavra[i]] == NULL){free(palavra);return NULL;}//caso um nó não tenha um ponteiro para a próxima letra, retorna 0
		no = no->ramos[palavra[i]];
		i++;
	}
}

void removepalavra(Notrie* no, char* palavrachar, int id){
	int* palavra = tratapalavra(palavrachar);
	int i = 0;
	while(1){
		if(palavra[i] == -1){
			if(no->lista != NULL){
				remover_no(no->lista, id);
				free(palavra);
				return;
			}
			else{
				free(palavra);
				return;
			}
		}
		if(no->ramos[palavra[i]] == NULL){
			free(palavra);
			return;}//caso um nó não tenha um ponteiro para a próxima letra, retorna 0
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



