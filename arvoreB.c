#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

#define B 5
#define T 3 //2t-1 = b <=> 2t-1 = 5 => t = 3

typedef struct no {
    int n;                   //numero total de elementos inseridos num no
    int folha;               //booleano, verifica se o no e folha
    int *chave;              //vetor de chaves
    struct no **filho;       //vetor de ponteiros que apontam para os filhos
}NoArvB;

typedef struct arvB {
    int t;              //termo limitador de elementos num no
    int b;              //numero de chaves num no
    NoArvB *raiz;       //raiz da arvore
}ArvoreB;

void criaArvore(ArvoreB *arvB, int t) {
    int b = 2*t-1;

    arvB->t = t;
    arvB->b = b;

    NoArvB *x = (NoArvB*)malloc(sizeof(NoArvB));      //aloca novo no na memoria
    x->folha = 1;                                     //como a arovre esta sendo criada, o no e folha
    x->n = 0;                                         //numero de elementos dentro do no e zero
    x->chave = (int*)malloc(b*sizeof(int));
    x->filho = (NoArvB**)malloc(1+b*sizeof(NoArvB));
    //Escrita(x);
    arvB->raiz = x;                                   //atribui no a raiz da arvore B

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

void RemoveArvoreB(NoArvB *r, int k) {

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

    int language, menu;

    do{
        printf("Select your language: "
               "\n[1] English"
               "\n[2] Portuguese (Coming soon...)\n\n");
        scanf("%d",&language);

        system("cls");
    }while(language<1 || language>2);

    int t, k;

    switch(language) {
        case 1:
            printf("\n\tWelcome to the B Tree interface!\n\n");
            system("pause");
            system("cls");

            do{
                printf("\n[1] Create B Tree"
                       "\n[2] Destroy B Tree"
                       "\n[3] Search an element"
                       "\n[4] Insert an element"
                       "\n[5] Remove an element"
                       "\n[6] Print B Tree"
                       "\n[0] Exit\n\n");
                scanf("%d",&menu);

                system("cls");

                switch(menu) {
                    case 0:
                        break;

                    case 1:
                        if(arvB->raiz == NULL) {
                            do{
                                printf("\nChoose the t value (an integer t>=2): ");
                                scanf("%d",&t);

                                system("cls");
                            }while(t<2);

                            criaArvore(arvB, t);
                        }
                        else{
                            printf("\nA B Tree already exists in memory. Destroy it before creating another one.\n\n");
                            system("pause");
                            system("cls");
                        }

                        break;

                    case 2:

                        break;

                    case 3:
                        if(arvB->raiz != NULL) {
                            if(arvB->raiz->chave[0] != NULL) {
                                printf("Type the element you are looking for: ");
                                scanf("%d",&k);

                                BuscaArvoreB(arvB->raiz, k);
                            }
                            else{
                                printf("Insert an element before searching for it!\n\n");
                                system("pause");
                                system("cls");
                            }
                        }
                        else{
                            printf("Create a B Tree before searching for an element!\n\n");
                            system("pause");
                            system("cls");
                        }

                        break;

                    case 4:
                        if(arvB != NULL) {
                            printf("Type the element you want to insert: ");
                            scanf("%d",&k);

                            InsereArvoreB(arvB->raiz, k);
                        }
                        else{
                            printf("Create a B Tree before inserting an element!\n\n");
                            system("pause");
                            system("cls");
                        }

                        break;

                    case 5:

                        break;

                    case 6:
                        if(arvB != NULL) {
                            ImprimeArvoreB(arvB->raiz, 0);
                        }
                        else{
                            printf("Create a B Tree before printing it!\n\n");
                            system("pause");
                            system("cls");
                        }

                        break;

                    default:
                        printf("\nChoose a valid option!\n\n");
                        system("pause");
                        system("cls");

                        break;
                }

            }while(menu!=0);

            break;

        case 2:
            printf("\n\tBem-vindo à interface de Árvore B\n\n");
            system("pause");
            system("cls");

            do{
                menu = 0;
            }while(menu!=0);

            break;
    }

    return 0;
}
