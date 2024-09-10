#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

#define B 5
#define T 3 //2t-1 = b <=> 2t-1 = 5 => t = 3

typedef struct no {
    int n;                    //numero total de elementos inseridos num no
    int folha;                //booleano, verifica se o no e folha
    int chave[B];           //vetor de chaves
    struct no *filho[B+1];  //vetor de ponteiros que apontam para os filhos
}NoArvB;

typedef struct arvB {
    int t;              //termo limitador de elementos num no
    int b;              //numero de chaves num no
    NoArvB *raiz;       //raiz da arvore
}ArvoreB;

void criaArvore(ArvoreB *arvB) {
    NoArvB *x = (NoArvB*)malloc(sizeof(NoArvB)); //aloca novo no na memoria
    x->folha = 1;                                //como a arovre esta sendo criada, o no e folha
    x->n = 0;                                    //numero de elementos dentro do no e zero
    //Escrita(x);
    arvB->raiz = x;                              //atribui no a raiz da arvore B
}

int BuscaArvoreB(NoArvB *r, int k) { //r = raiz; k = elemento de busca
    int i=0; //indice comeca no 0 em c

    while(i<=r->n && k>r->chave[i]) { //verifica se i é menor ou igual o tamanho total de chaves ocupadas do no
        i++;                          //e se k é maior que a chave na posicao i
    }                                 //enquanto sim, i aumenta para percorrer o restante do no

    if(i<=r->n && k==r->chave[i]) { //verifica se i é menor ou igual o tamanho de chaves ocupadas do no
        return 1;                  //e se k é igual a chave na posicao i
    }                              //se sim, retorna que sim
    if(r->folha) {         //se nao achou, verifica se no é folha
        return 0;       //se sim, retorna que nao achou
    }
    else {                                       //se nao achou e tem filho, procura no filho
        //Leitura(r->filho[i];                   //le o filho no disco
        return BuscaArvoreB(r->filho[i], k);     //funcao recursiva no filho
    }
}

void SplitChildArvoreB(NoArvB *x, int i) { //x = no pai do no onde o elemento sera inserido; i = indice do no filho
    NoArvB *z = (NoArvB*)malloc(sizeof(NoArvB));
    z->folha = x->filho[i]->folha;                                  //ERRO AQUI
    z->n = T-1;

    for(int j=0; j<T-1; j++) {
        z->chave[j] = x->filho[i]->chave[j+T];
    }

    if(!x->filho[i]->folha) {
        for(int j=0; j<T; j++) {
            z->filho[j] = x->filho[i]->filho[j+T];
        }
    }

    x->filho[i]->n = T-1;

    for(int j=x->n+1; j>i+1; j--) {
        x->filho[j+1] = x->filho[j];
    }

    x->filho[i+1] = z;

    for(int j=x->n; j>i; j--) {
        x->chave[j+1] = x->chave[j];
    }

    x->chave[i] = x->filho[i]->chave[T];
    x->n++;

    //Escrita(x->filho[i]);
    //Escrita(z);
    //Escrita(x);
}

void InsereNaoCheioArvoreB(NoArvB *x, int k) {  //x = no onde sera inserido o elemento; k = elemento a ser inserido
    int i = x->n; //indice que comeca no fim do no

    if(x->folha) { //verifica se o no x e folha
        while(i>=0 && k<x->chave[i]) {      //enquanto i for maior ou igual a 0 e k menor que a chave na posicao i
            x->chave[i+1] = x->chave[i];    //chave da posicao seguinte recebe chave da posicao atual
            i--;                            //i diminui (vai pra esquerda)
        }
        x->chave[i+1] = k;              //chave da posicao seguinte recebe o elemento
        x->n++;                         //numero de chaves ocupadas do no aumenta 1
        //Escrita(x);
    }
    else { //se x nao for folha
        while(i>=0 && k<x->chave[i]) {  //enquanto i for maior ou igual a 0 e k menor que o elemento da chave na posicao i
            i--;                        //i diminui (indice vai pra esquerda)
        }
        i++;       //i aumenta (indice vai pra esquerda)

        //Leitura(x->filho[i];

        if(x->filho[i]->n == 2*T-1) {  //verifica se o filho na posicao i vezes o numero de chaves preenchidas e igual a b pra ver se o no esta cheio
            SplitChildArvoreB(x, i);   //faz split

            if(k>x->chave[i]) {   //se k for maior que chave na posicao i
                i++;   //i aumenta (indice vai pra direita)
            }
        }

        InsereNaoCheioArvoreB(x->filho[i], k); //faz a propria funcao no filho
    }
}

void InsereArvoreB(NoArvB *r, int k) { //r = raiz; k = elemento a ser inserido; t = termo de limitacao
    if(r->n == 2*T-1) {    //verifica se o no esta cheio pela equacao com o termo t
        NoArvB *s = (NoArvB*)malloc(sizeof(NoArvB));    //se esta cheio, alocar novo no (raiz)
        s->folha = 0;                  //folha vazia, ie, ele mesmo e folha
        s->n = 0;                      //numero de elementos no no = 0
        s->filho[0] = r;               //ponteiro do novo no aponta pra raiz
        SplitChildArvoreB(s, 1);       //faz split                                                             //ERRO AQUI
        InsereNaoCheioArvoreB(s, k);   //insere o elemento no novo no
    }
    else {                            //se nao esta cheio
        InsereNaoCheioArvoreB(r, k);  //insere no no
    }
}

void ImprimeArvoreB(NoArvB *r, int nivel) {
    if (r == NULL) return;

    int i;
    for(i=0; i<r->n; i++) {
        //imprime o filho da esquerda (subárvore) recursivamente
        if (!r->folha) {
            ImprimeArvoreB(r->filho[i], nivel+1);
        }

        //imprime o nivel e a chave do no
        for(int j=0; j<nivel; j++) {
            printf("    ");  //imprime espaços para formatar a arvore
        }
        printf("%d\n", r->chave[i]);
    }

    //imprime o último filho (subárvore)
    if (!r->folha) {
        ImprimeArvoreB(r->filho[i], nivel+1);
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    ArvoreB *arvB = (ArvoreB*)malloc(sizeof(ArvoreB));
    arvB->b = B;
    arvB->t = T;

    criaArvore(arvB);

    InsereArvoreB(arvB->raiz, 10);
    InsereArvoreB(arvB->raiz, 5);
    InsereArvoreB(arvB->raiz, 15);
    InsereArvoreB(arvB->raiz, 20);
    InsereArvoreB(arvB->raiz, 5);
    InsereArvoreB(arvB->raiz, 2);
    InsereArvoreB(arvB->raiz, 22);

    ImprimeArvoreB(arvB->raiz, 0);

    return 0;
}
