#include <stdio.h>
#include "auxiliares.h"
#include "lista.h"

int main(){
  char controle[100], nomearq[50];

	printf("Insira o nome do arquivo\n");
	scanf("%s", nomearq);
  LISTA * lista = le_csv(nomearq);
  if(lista == NULL) return 0;

	while(controle[0]!='6'){
		printf("1. Inserir um site\n2. Remover um site\n3. Inserir palavra-chave\n4. Atualizar relevância\n5. Exibir sites \n6. Sair\n");
		scanf("%s", controle);

		switch(controle[0]){
			case '1':
          Inserir_Site(lista);
			break;
			case '2':
          Remover_Site(lista);
			break;
			case '3':
          Inserir_Keyword(lista);
			break;
			case '4':
          Atualizar_Relevancia(lista);
			break;
			case '5':
          descarrega_lista(lista, stdout);
			break;
      case '6':
          Sair(lista, nomearq);
      break;
			default:
				printf("\nComando incorreto!!!!!\n\tescolha uma opcao valida:\n\n");
			break;
		}
	}

	return 0;
}
