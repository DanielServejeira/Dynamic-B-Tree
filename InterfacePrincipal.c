#include<stdio.h>
#include<locale.h>

#include "arvoreB.h"
#include "funcoesDisco.h"

int main() {
    setlocale(LC_ALL, "Portuguese");

    int idioma, menuArq;
    char *arquivo;

    do{
        printf("Select your language: "
               "\n[1] English"
               "\n[2] Portuguese (Coming soon...)\n\n");
        scanf("%d",&idioma);

        system("cls");
    }while(idioma<1 || idioma>2);

    switch(idioma) {
        case 1:
            do{
                printf("\n[1] Create a file"
                       "\n[2] Delete a file"
                       "\n[3] Modify a file"
                       "\n[0] Exit\n\n");
                scanf("%d",&menuArq);

                fflush(stdin);

                switch(menuArq) {
                    case 0:
                        break;

                    case 1:
                        criaArquivo();
                        break;

                    case 2:
                        deletaArquivo();
                        break;

                    case 3:
                        arquivo = escolheArquivo();

                        if(arquivo != NULL) {
                            FILE *file = fopen(arquivo, "r+");

                            if(file != NULL) {
                                interfaceArvBIngles(file);
                                fclose(file);
                            }
                            else {
                                printf("Error opening file '%s'.\n", arquivo);
                            }
                            free(arquivo);
                        }
                        else {
                            printf("No valid file chosen.\n");
                        }
                        break;

                    default:
                        printf("\nChoose a valid option!\n\n");
                        break;
                }

                printf("\n");
                system("pause");
                system("cls");

            }while(menuArq!=0);

            break;

        case 2:
            printf("\n\tBem-vindo à interface de Árvore B\n\n");
            system("pause");
            system("cls");

            do{
                menuArq = 0;
            }while(menuArq!=0);

            break;
    }

    return 0;
}
