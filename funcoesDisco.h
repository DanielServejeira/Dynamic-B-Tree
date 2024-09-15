#ifndef FUNCOES_DISCO
#define FUNCOES_DISCO

void Escrita(FILE *arquivo, NoArvB *x, int posicao);
void Leitura(FILE *arquivo, NoArvB *x, int posicao);
void criaArquivo();
void deletaArquivo();
char *escolheArquivo();

#include "funcoesDisco.c"

#endif
