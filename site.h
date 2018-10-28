#ifndef SITE_H
#define SITE_H
#define disponivel -1
#define ERRO NULL
#define erro -32000

typedef struct Site{
  int id;
  char nome[50];
  int rel;
  char link[100];
  char keywords[10][50];
  int nrowords;
} SITE;

SITE * criar_site(int id, char * nome, int relevancia, char * link, char ** keywords, int nrowords);
void copia_site(SITE * s1, SITE * s2);
void alterar_relevancia(SITE * s, int relevancia);
void remover_site(SITE * s);
void inserir_keyword(SITE * s, char * keyword);
void descarregar_site(FILE * arq, SITE * s);
void liberar_site(SITE * s);

#endif
