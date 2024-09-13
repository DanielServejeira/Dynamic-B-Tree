#include<stdio.h>
#include<stdlib.h>
#include<math.h>
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

void CriaArvore(ArvoreB *arvB) {
    NoArvB *x = (NoArvB*)malloc(sizeof(NoArvB)); //aloca novo no na memoria
    x->folha = 1;                                //como a arovre esta sendo criada, o no e folha
    x->n = 0;                                    //numero de elementos dentro do no e zero
    //Escrita(x);
    arvB->raiz = x;                              //atribui no a raiz da arvore B
}

int BuscaNo(NoArvB *r, int k) { //r = raiz; k = elemento de busca
    int esquerda = 0, direita = r->n - 1, meio;
    float media;

    while (esquerda <= direita) {
        media = (float)(esquerda + direita) / 2; 
        meio = ceil(media); // Usa ceil para padronizar o arredondamento para cima

        if (r->chave[meio] == k) {
            return 1; // Chave encontrada
        } else if (r->chave[meio] < k) {
            esquerda = ++meio;
        } else {
            direita = meio - 1;
        }
    }

    return -meio; // Retorna negativo para dizer que nao encontrou e a posicao onde deveria estar
}

void SplitChildArvoreB(NoArvB *x, int i) { //x = no pai do no onde o elemento sera inserido; i = indice do no filho
    NoArvB *z = (NoArvB*)malloc(sizeof(NoArvB));
    NoArvB *y = x->filho[i];
    z->folha = y->folha;
    z->n = T-1;

    for(int j=0; j<T-1; j++) {
        z->chave[j] = y->chave[j+T];
    }

    if(!y->folha) {
        for(int j=0; j<T; j++) {
            z->filho[j] = y->filho[j+T];
        }
    }

    y->n = T-1;

    for(int j=x->n+1; j>i+1; j--) {                         // ERRO AQUI
        x->filho[j+1] = x->filho[j];
    }

    x->filho[i+1] = z;

    for(int j=x->n; j>i; j--) {
        x->chave[j+1] = x->chave[j];
    }

    x->chave[i] = y->chave[T];
    x->n++;

    //Escrita(y);
    //Escrita(z);
    //Escrita(x);
}

void InsereNaoCheioArvoreB(NoArvB *x, int k, int pos) {  //x = no onde sera inserido o elemento; k = elemento a ser inserido
    if (x->n == pos) {
        x->chave[pos] = k;
        x->n++;
    } else {
        for (int i = x->n; i > pos; i--) {
            x->chave[i] = x->chave[i - 1];
        }
        x->chave[pos] = k;
        x->n++;
    }
}

void InsereArvoreB(NoArvB *r, int k) { //r = raiz; k = elemento a ser inserido; t = termo de limitacao

    // Busca no nó pra ver se tem o elemento
    int busca;
    while (1)
    {
        busca = BuscaNo(r, k);
        if (busca > 0) return; // Se a busca retornar positivo, o elemento já existe, então não insere

        if (r->folha)
        {
            break; // Se o nó for folha, então sai do loop para inserir o elemento
        }

        // Se não for folha, então vai para o filho onde o elemento deveria estar e busca de novo
        r = r->filho[-busca]; // Se a busca retornar negativo, o elemento não existe e x é o filho onde o elemento deveria estar inserido
    }

    if(r->n == 2*T-1) {    //verifica se o no esta cheio pela equacao com o termo t
        NoArvB *s = (NoArvB*)malloc(sizeof(NoArvB));    //se esta cheio, alocar novo no (raiz)
        s->folha = 0;                  //folha vazia, ie, ele mesmo e folha
        s->n = 0;                      //numero de elementos no no = 0
        s->filho[1] = r;               //ponteiro do novo no aponta pra raiz
        SplitChildArvoreB(s, 1);       //faz split

        InsereNaoCheioArvoreB(s, k, 0);   //insere o elemento no novo no
    }
    else {                            //se nao esta cheio
        InsereNaoCheioArvoreB(r, k, -busca);  //insere no no 
    }
}

void ImprimeArvoreB(NoArvB *r, int nivel) {
    if (r == NULL) {
        printf("Arvore vazia\n");
        return;
    }

    // Imprimir a indentação baseada no nível atual (inversamente proporcional ao nível)
    for (int i = 0; i < T * 2 - nivel; i++) {
        printf("\t");
    }

    // Imprimir chaves do nó atual
    for (int chaveIndex = 0; chaveIndex < r->n; chaveIndex++) {
        printf("|%d| ", r->chave[chaveIndex]);
    }
    printf("\n");

    // Se o nó não for uma folha, printar seus filhos recursivamente
    if (!r->folha) {
        for (int filhoIndex = 0; filhoIndex <= r->n; filhoIndex++) {
            ImprimeArvoreB(r->filho[filhoIndex], nivel + 1);
        }
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    ArvoreB *arvB = (ArvoreB*)malloc(sizeof(ArvoreB));

    arvB->b = B;
    arvB->t = T;

    CriaArvore(arvB);

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
