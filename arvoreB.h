#ifndef ARVORE_B
#define ARVORE_B

typedef struct no {
    int nome[16];            //nome aleatorio do no de 16 caracteres
    int n;                   //numero total de elementos inseridos num no
    int folha;               //booleano, verifica se o no e folha
    int *chave;              //vetor de chaves
    struct no **filho;       //vetor de ponteiros que apontam para os filhos
}NoArvB;

typedef struct arvB {
    int t;
    NoArvB *raiz;
}ArvoreB;

void CriaArvoreB(ArvoreB *arvB, int t);
void DestroiArvoreB(ArvoreB *arvB);
int BuscaArvoreB(NoArvB *r, int k);
int BuscaNo(NoArvB *r, int k);
void SplitChildArvoreB(NoArvB *raiz, int i, int t);
void InsereNaoCheioArvoreB(NoArvB *x, int k, int t);
void InsereArvoreB(NoArvB *r, int k, int t);
void RemoveArvoreB(NoArvB *r, int k, int t);
void ImprimeArvoreB(NoArvB *r, int nivel, int t);
void InterfaceArvBIngles(FILE *arquivo, char diretorio[]);

#include "arvoreB.c"

#endif
