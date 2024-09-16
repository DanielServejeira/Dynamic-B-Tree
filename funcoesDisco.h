#ifndef FUNCOES_DISCO
#define FUNCOES_DISCO

#include "arvoreB.h"

char *geraNomeArquivo();
FILE *criaArquivoBinario();
void Escrita(FILE *arquivo, NoArvB *x, int posicao);
void Leitura(FILE *arquivo, NoArvB *x, int posicao);
void criaDiretorio();
void deletaDiretorio();
char *escolheDiretorio();

#include "funcoesDisco.c"

#endif
