#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>

#include "funcoesDisco.h"

char *geraNomeArquivo() {
    char nome[16];
    const char caracteres[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

    //inicializa a semente para a fun��o rand usando o tempo atual
    srand(time(NULL));

    //gera 16 caracteres aleat�rios
    for(int i=0; i<16; i++) {
        nome[i] = caracteres[rand()%(sizeof(caracteres)-1)];
    }

    nome[16] = '\0';

    return nome;
}

FILE *criaArquivoBinario() {
    char nomeArquivo[16];  //nome com 16 caracteres
    strcpy(nomeArquivo, geraNomeArquivo());  //gera um nome de 16 caracteres

    FILE *file = fopen(nomeArquivo, "wb+");
    if(file == NULL) {
        printf("Error creating file %s.\n", nomeArquivo);
        return NULL;
    }

    printf("File '%s' created successfully!\n", nomeArquivo);

    fclose(file);

    return file;
}

void Escrita(FILE *arquivo, NoArvB *x, int posicao) {
    fseek(arquivo, posicao*sizeof(NoArvB), SEEK_SET);
    fwrite(x, sizeof(NoArvB), 1, arquivo);
}

void Leitura(FILE *arquivo, NoArvB *x, int posicao) {
    fseek(arquivo, posicao*sizeof(NoArvB), SEEK_SET);
    fread(x, sizeof(NoArvB), 1, arquivo);
}

void criaDiretorio() {
    char aux[256];

    printf("\nName the directory: ");
    fgets(aux, 256, stdin);
    aux[strcspn(aux, "\n")] = 0;  //remove o newline do final

    //cria o diret�rio
    if (_mkdir(aux, 0777) == 0) {
        printf("Directory '%s' created successfully!\n", aux);
    } else {
        printf("Error creating the directory!\n");
    }
}

void deletaDiretorio() {
    struct dirent *de;
    DIR *dr = opendir(".");

    if (dr == NULL) {
        printf("Error opening directory.\n");
        return;
    }

    char diretorios[100][256];  // Array para armazenar os nomes dos diret�rios
    int cont = 0;

    printf("\nAvailable directories for deletion:\n");

    // Listar diret�rios no diret�rio atual
    while ((de = readdir(dr)) != NULL) {
        struct stat st;
        if (stat(de->d_name, &st) == 0 && S_ISDIR(st.st_mode)) {
            // Ignorar diret�rios "." e ".."
            if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0) {
                printf("[%d] %s\n", cont, de->d_name);  // Mostra o �ndice e o nome do diret�rio
                strcpy(diretorios[cont], de->d_name);   // Copia o nome do diret�rio para o array
                cont++;
            }
        }
    }

    closedir(dr);

    if (cont == 0) {
        printf("No directories available for deletion.\n");
        return;
    }

    int escolha;
    printf("\nChoose the directory to delete by index: ");
    scanf("%d", &escolha);
    getchar();  //limpa o buffer

    if (escolha < 0 || escolha >= cont) {
        printf("Invalid index!\n");
        return;
    }

    // Deleta o diret�rio escolhido
    if (rmdir(diretorios[escolha]) == 0) {
        printf("Directory '%s' deleted successfully.\n", diretorios[escolha]);
    } else {
        printf("Error deleting directory '%s'.\n", diretorios[escolha]);
    }
}

char *escolheDiretorio() {
    struct dirent *de;
    DIR *dr = opendir(".");

    if (dr == NULL) {
        printf("Error opening directory.\n");
        return NULL;
    }

    char diretorios[100][256];  // Array para armazenar os nomes dos diret�rios
    int cont = 0;

    printf("Available directories:\n");

    // Listar diret�rios no diret�rio atual
    while ((de = readdir(dr)) != NULL) {
        struct stat st;
        if (stat(de->d_name, &st) == 0 && S_ISDIR(st.st_mode)) {
            //ignorar diret�rios "." e ".."
            if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0) {
                printf("[%d] %s\n", cont, de->d_name);  // Mostra o �ndice e o nome do diret�rio
                strcpy(diretorios[cont], de->d_name);   // Copia o nome do diret�rio para o array
                cont++;
            }
        }
    }

    closedir(dr);

    if (cont == 0) {
        printf("No directories available.\n");
        return NULL;
    }

    int escolha;
    printf("\nChoose the directory by index: ");
    scanf("%d", &escolha);
    getchar();  //limpa o buffer

    if (escolha < 0 || escolha >= cont) {
        printf("Invalid index!\n");
        return NULL;
    }

    // Aloca mem�ria para o nome do diret�rio escolhido e retorna
    char *diretorioEscolhido = malloc(strlen(diretorios[escolha]) + 1);
    if (diretorioEscolhido == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    strcpy(diretorioEscolhido, diretorios[escolha]);

    return diretorioEscolhido;
}
