#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include "arvoreB.h"
#include "funcoesDisco.h"

void CriaArvoreB(ArvoreB *arvB, int t) {
    int b = 2*t-1;

    NoArvB *x = (NoArvB*)malloc(sizeof(NoArvB));      //aloca novo no na memoria
    x->folha = 1;                                     //como a arvore esta sendo criada, o no e folha
    x->n = 0;                                         //numero de elementos dentro do no e zero
    x->chave = (int*)malloc(b*sizeof(int));
    x->filho = (NoArvB**)malloc(1+b*sizeof(NoArvB));
    //Escrita(x);
    arvB->raiz = x;                                   //atribui no a raiz da arvore B
    arvB->t = t;
}

int BuscaNo(NoArvB *r, int k) { //r = raiz; k = elemento de busca
    int esquerda = 0, direita = r->n - 1, meio;
    float media;

    while(esquerda <= direita) {
        media = (float)(esquerda + direita) / 2;
        meio = ceil(media); //usa ceil para padronizar o arredondamento para cima

        if (r->chave[meio] == k) {
            return 1; //chave encontrada
        }
        else if (r->chave[meio] < k) {
            esquerda = ++meio;
        }
        else {
            direita = meio - 1;
        }
    }

    return -meio; //retorna negativo para dizer que nao encontrou e a posicao onde deveria estar
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

void SplitChildArvoreB(NoArvB *x, int i, int t) { // x = nó pai do nó onde será feito o split; i = índice do nó filho
    NoArvB *novoNo = (NoArvB*)malloc(sizeof(NoArvB));
    NoArvB *filho = x->filho[i];
    novoNo->folha = filho->folha;
    novoNo->n = t - 1;

    for (int j = 0; j < t - 1; j++) {
        novoNo->chave[j] = filho->chave[j + t];
    }

    if (!filho->folha) {
        for (int j = 0; j < t; j++) {
            novoNo->filho[j] = filho->filho[j + t];
        }
    }

    filho->n = t - 1;

    for (int j = x->n; j >= i + 1; j--) {
        x->filho[j + 1] = x->filho[j];
    }

    x->filho[i + 1] = novoNo;

    for (int j = x->n - 1; j >= i; j--) {
        x->chave[j + 1] = x->chave[j];
    }

    x->chave[i] = filho->chave[t - 1];
    x->n++;

    //Escrita(filho);
    //Escrita(novoNo);
    //Escrita(x);
}

void InsereNaoCheioArvoreB(NoArvB *x, int k, int t) {  // x = nó onde será inserido o elemento; k = elemento a ser inserido
    int i = x->n - 1;

    if (x->folha) {
        while (i >= 0 && k < x->chave[i]) {
            x->chave[i + 1] = x->chave[i];
            i--;
        }
        x->chave[i + 1] = k;
        x->n++;
    } else {
        while (i >= 0 && k < x->chave[i]) {
            i--;
        }
        i++;
        if (x->filho[i]->n == 2 * t - 1) {
            SplitChildArvoreB(x, i, t);
            if (k > x->chave[i]) {
                i++;
            }
        }
        InsereNaoCheioArvoreB(x->filho[i], k, t);
    }
}

void InsereArvoreB(NoArvB *x, int k, int t) { // r = raiz; k = elemento a ser inserido; t = termo de limitação
    NoArvB *r = x;

    if (r->n == 2 * t - 1) {    // verifica se o nó está cheio pela equação com o termo t
        NoArvB *s = (NoArvB*)malloc(sizeof(NoArvB));    // se está cheio, alocar novo nó (raiz)
        x = s;
        s->folha = 0;                  // não é folha
        s->n = 0;                      // número de elementos no nó = 0
        s->filho[0] = r;               // ponteiro do novo nó aponta para a raiz
        SplitChildArvoreB(s, 0, t);       // faz split

        InsereNaoCheioArvoreB(s, k, t);   // insere o elemento no novo nó
    } else {
        InsereNaoCheioArvoreB(r, k, t);
    }
}

void RemoveArvoreB(NoArvB *r, int k, int t) {
    int i=0;

    while(i<r->n && k!=r->chave[i]) i++;

    if(i!=2*t && r->folha) {
        r->chave[i] = NULL;
        r->n--;
    }
    else if(i!=2*t && !r->folha) {
        if(r->filho[i] >= t) {
            RemoveArvoreB(r, r->chave[i-1], t);
            r->chave[i] = r->chave[i-1];
        }
        else if(r->filho[i+1] >= t) {
            RemoveArvoreB(r, r->chave[i], t);
            r->chave[i+1] = r->chave[i];
        }
        else{

            RemoveArvoreB(r, r->chave[i-1], t);
        }
    }
    else {
        i=0;

        while(i<=r->n-1 && k>r->chave[i]) i++;
        if(r->filho[i]->n == t-1) {
            int j=0;

            while(r->filho[j]->n >= t) j++;

            if(j<r->n) {
                r->filho[i]->chave[r->filho[i]->n] = r->chave[i];
                r->filho[i]->n++;
            }
            else {

            }

            RemoveArvoreB(r->filho[i], k, t);
        }
    }

}

void ImprimeArvoreB(NoArvB *r, int nivel, int t) {
    if (r == NULL) {
        printf("Empty tree\n");
        return;
    }

    // Imprimir a indentação baseada no nível atual (inversamente proporcional ao nível)
    for (int i = 0; i < t*2 - nivel; i++) {
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
            ImprimeArvoreB(r->filho[filhoIndex], nivel + 1, t);
        }
    }
}

void InterfaceArvBIngles(FILE *arquivo, char diretorio[]) {
    ArvoreB *arvB = NULL;
    int menuArvB, t, k;

    printf("\n\tWelcome to the B Tree interface from %s!\n\n",diretorio);
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
        scanf("%d",&menuArvB);

        system("cls");

        switch(menuArvB) {
            case 0:
                break;

            case 1:
                if(arvB == NULL) {
                    arvB = (ArvoreB*)malloc(sizeof(ArvoreB));

                    do{
                        printf("\nChoose the t value (an integer t>=2): ");
                        scanf("%d",&t);
                    }while(t<2);

                    CriaArvoreB(arvB, t);
                }
                else printf("\nA B Tree already exists in memory. Destroy it before creating another one.\n");

                printf("\n");
                system("pause");
                system("cls");

                break;

            case 2:
                //if(arvB!=NULL) DestroiArvoreB(ArvoreB *arvB);
                break;

            case 3:
                if(arvB != NULL) {
                    if(arvB->raiz->chave[0] != NULL) {
                        printf("\nType the element you are looking for: ");
                        scanf("%d",&k);

                        printf("\n\t%d\n", BuscaArvoreB(arvB->raiz, k));
                    }
                    else printf("\nInsert an element before searching for it!\n");
                }
                else printf("\nCreate a B Tree before searching for an element!\n");

                printf("\n");
                system("pause");
                system("cls");

                break;

            case 4:
                if(arvB != NULL) {
                    printf("\nType the element you want to insert: ");
                    scanf("%d",&k);

                    InsereArvoreB(arvB->raiz, k, t);
                }
                else printf("\nCreate a B Tree before inserting an element!\n");

                printf("\n");
                system("pause");
                system("cls");

                break;

            case 5:
                //if(arvB!=NULL) RemoveArvoreB(NoArvB *raiz, int k, int t);
                break;

            case 6:
                if(arvB != NULL) ImprimeArvoreB(arvB->raiz, 0, t);
                else printf("\nCreate a B Tree before printing it!\n");

                printf("\n");
                system("pause");
                system("cls");

                break;

            default:
                printf("\nChoose a valid option!\n\n");

                system("pause");
                system("cls");

                break;
        }

    }while(menuArvB!=0);
}
