#ifndef ARVORE_B
#define ARVORE_B

typedef struct no {
    int n;                   //numero total de elementos inseridos num no
    int folha;               //booleano, verifica se o no e folha
    int *chave;              //vetor de chaves
    struct no **filho;       //vetor de ponteiros que apontam para os filhos
}NoArvB;

typedef struct arvB {
    NoArvB *raiz;
}ArvoreB;

void criaArvore(ArvoreB *arvB, int t);
int BuscaNo(NoArvB *r, int k);
void SplitChildArvoreB(NoArvB *x, int i, int t);
void InsereNaoCheioArvoreB(NoArvB *x, int k, int pos);
void InsereArvoreB(NoArvB *r, int k, int t);
void RemoveArvoreB(NoArvB *r, int k, int t);
void ImprimeArvoreB(NoArvB *r, int nivel, int t);
void interfaceArvBIngles(FILE *arquivo);

#include "arvoreB.c"

#endif
