#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

void Escrita(FILE *arquivo, NoArvB *x, int posicao) {
    fseek(arquivo, posicao*sizeof(NoArvB), SEEK_SET);
    fwrite(x, sizeof(NoArvB), 1, arquivo);
}

void Leitura(FILE *arquivo, NoArvB *x, int posicao) {
    fseek(arquivo, posicao*sizeof(NoArvB), SEEK_SET);
    fread(x, sizeof(NoArvB), 1, arquivo);
}

void criaArquivo() {
    char aux[32];

    printf("\nName the archive: ");
    fgets(aux, 32, stdin);
    aux[strcspn(aux, "\n")] = 0;

    if (strstr(aux, ".dat") == NULL) {
        strcat(aux, ".dat");
    }

    FILE *file = fopen(aux, "wb+");

    if (file == NULL) {
        printf("Error creating the file!\n");
    } else {
        printf("File '%s' created successfully!\n", aux);
        fclose(file);
    }
}

void deletaArquivo() {
    struct dirent *de;
    DIR *dr = opendir(".");

    if (dr == NULL) {
        printf("\nError opening directory\n");
        return;
    }

    char arquivos[100][256];  //array que armazena os arquivos binarios
    int cont = 0;

    printf("\nAvailable .dat files for deletion:\n");

    // List .dat files in the directory
    while ((de = readdir(dr)) != NULL) {
        struct stat st;
        if (stat(de->d_name, &st) == 0 && S_ISREG(st.st_mode)) {
            if (strstr(de->d_name, ".dat") != NULL) {
                printf("[%d] %s\n", cont, de->d_name);
                strcpy(arquivos[cont], de->d_name);
                cont++;
            }
        }
    }

    closedir(dr);

    if(cont == 0) {
        printf("No .dat files available for deletion.\n");
        return;
    }

    int escolha;
    printf("\nChoose the file to delete by index: ");
    scanf("%d", &escolha);
    getchar();  // Clear the newline buffer

    if(escolha < 0 || escolha >= cont) {
        printf("Invalid index!\n");
        return;
    }

    // Delete the chosen file
    if(remove(arquivos[escolha]) == 0) {
        printf("File '%s' deleted successfully.\n", arquivos[escolha]);
    } else {
        printf("Error deleting the file '%s'.\n", arquivos[escolha]);
    }
}

char *escolheArquivo() {
    struct dirent *de;
    DIR *dr = opendir(".");

    if(dr == NULL) {
        printf("Error opening directory.\n");
        return NULL;
    }

    char arquivos[100][256];  //array que armazena os arquivos binarios
    int cont = 0;

    printf("Available .dat files:\n");

    //lista os arquivos binarios do diretorio
    while((de = readdir(dr)) != NULL) {
        struct stat st;
        if (stat(de->d_name, &st) == 0 && S_ISREG(st.st_mode)) {
            if (strstr(de->d_name, ".dat") != NULL) {
                printf("[%d] %s\n", cont, de->d_name);
                strcpy(arquivos[cont], de->d_name);
                cont++;
            }
        }
    }

    closedir(dr);

    if (cont == 0) {
        printf("No .dat files available.\n");
        return NULL;
    }

    int escolha;
    printf("\nChoose the file by index: ");
    scanf("%d", &escolha);
    getchar();  //limpa o buffer

    if (escolha < 0 || escolha >= cont) {
        printf("Invalid index!\n");
        return NULL;
    }

    char *arquivoEscolhido = malloc(strlen(arquivos[escolha]) + 1);
    if (arquivoEscolhido == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    strcpy(arquivoEscolhido, arquivos[escolha]);

    return arquivoEscolhido;
}
