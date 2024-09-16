#include<stdio.h>
#include<locale.h>

#include "funcoesDisco.h"
#include "arvoreB.h"

int main() {
    setlocale(LC_ALL, "Portuguese");

    int idioma, menuArq;
    char *diretorio;

    do{
        printf("By Daniel Servejeira & Raphael Leiva\n"
               "\nSelect your language: "
               "\n[1] English"
               "\n[2] Portuguese (Coming soon...)\n\n");
        scanf("%d",&idioma);

        system("cls");
    }while(idioma<1 || idioma>2);

    switch(idioma) {
        case 1:
            do{
                printf("\n[1] Create a directory"
                       "\n[2] Delete a directory"
                       "\n[3] Modify a directory"
                       "\n[0] Exit\n\n");
                scanf("%d",&menuArq);

                fflush(stdin);

                switch(menuArq) {
                    case 0:
                        break;

                    case 1:
                        criaDiretorio();
                        break;

                    case 2:
                        deletaDiretorio();
                        break;

                    case 3:
                        diretorio = escolheDiretorio();

                        if(diretorio != NULL) {
                            FILE *file = fopen(diretorio, "r+");
                            InterfaceArvBIngles(file, diretorio);
                            fclose(file);

                            free(diretorio);
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
