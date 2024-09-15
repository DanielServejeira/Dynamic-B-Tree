#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void criaArvore(ArvoreB *arvB, int t) {
    int b = 2*t-1;

    NoArvB *x = (NoArvB*)malloc(sizeof(NoArvB));      //aloca novo no na memoria
    x->folha = 1;                                     //como a arvore esta sendo criada, o no e folha
    x->n = 0;                                         //numero de elementos dentro do no e zero
    x->chave = (int*)malloc(b*sizeof(int));
    x->filho = (NoArvB**)malloc(1+b*sizeof(NoArvB));
    //Escrita(x);
    arvB->raiz = x;                                   //atribui no a raiz da arvore B
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

void SplitChildArvoreB(NoArvB *x, int i, int t) { //x = no pai do no onde o elemento sera inserido; i = indice do no filho
    NoArvB *z = (NoArvB*)malloc(sizeof(NoArvB));
    NoArvB *y = x->filho[i];
    z->folha = y->folha;
    z->n = t-1;

    for(int j=0; j<t-1; j++) {
        z->chave[j] = y->chave[j+t];
    }

    if(!y->folha) {
        for(int j=0; j<t; j++) {
            z->filho[j] = y->filho[j+t];
        }
    }

    y->n = t-1;

    for(int j=x->n+1; j>i+1; j--) {                         // ERRO AQUI
        x->filho[j+1] = x->filho[j];
    }

    x->filho[i+1] = z;

    for(int j=x->n; j>i; j--) {
        x->chave[j+1] = x->chave[j];
    }

    x->chave[i] = y->chave[t];
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

void InsereArvoreB(NoArvB *r, int k, int t) { //r = raiz; k = elemento a ser inserido; t = termo de limitacao

    //busca no nó pra ver se tem o elemento
    int busca;
    while(1) {
        busca = BuscaNo(r, k);
        if(busca > 0) return; //se a busca retornar positivo, o elemento já existe, então não insere

        if(r->folha) {
            break; // Se o nó for folha, então sai do loop para inserir o elemento
        }

        // Se não for folha, então vai para o filho onde o elemento deveria estar e busca de novo
        r = r->filho[-busca]; // Se a busca retornar negativo, o elemento não existe e x é o filho onde o elemento deveria estar inserido
    }

    if(r->n == 2*t-1) {    //verifica se o no esta cheio pela equacao com o termo t
        NoArvB *s = (NoArvB*)malloc(sizeof(NoArvB));    //se esta cheio, alocar novo no (raiz)
        s->folha = 0;                  //folha vazia, ie, ele mesmo e folha
        s->n = 0;                      //numero de elementos no no = 0
        s->filho[1] = r;               //ponteiro do novo no aponta pra raiz
        SplitChildArvoreB(s, 1, t);       //faz split

        InsereNaoCheioArvoreB(s, k, 0);   //insere o elemento no novo no
    }
    else {                            //se nao esta cheio
        InsereNaoCheioArvoreB(r, k, -busca);  //insere no no
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
        printf("Arvore vazia\n");
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

void interfaceArvBIngles(FILE *arquivo) {
    ArvoreB *arvB = (ArvoreB*)malloc(sizeof(ArvoreB));
    int menuArvB, t, k;

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
        scanf("%d",&menuArvB);

        system("cls");

        switch(menuArvB) {
            case 0:
                break;

            case 1:
                if(arvB->raiz == NULL) {
                    do{
                        printf("\nChoose the t value (an integer t>=2): ");
                        scanf("%d",&t);
                    }while(t<2);

                    criaArvore(arvB, t);
                }
                else printf("\nA B Tree already exists in memory. Destroy it before creating another one.\n");

                printf("\n");
                system("pause");
                system("cls");

                break;

            case 2:

                break;

            case 3:
                if(arvB->raiz != NULL) {
                    if(arvB->raiz->chave[0] != NULL) {
                        printf("\nType the element you are looking for: ");
                        scanf("%d",&k);

                        BuscaNo(arvB->raiz, k);
                    }
                    else printf("\nInsert an element before searching for it!\n");
                }
                else printf("\nCreate a B Tree before searching for an element!\n");

                printf("\n");
                system("pause");
                system("cls");

                break;

            case 4:
                if(arvB->raiz != NULL) {
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

                break;

            case 6:
                if(arvB->raiz != NULL) ImprimeArvoreB(arvB->raiz, 0, t);
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
