#include "estruturas.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define RED "\e[0;31m"
#define NC "\e[0m"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to ignore any comments
// in file
void proxLinhaDescomentada(FILE* fp)
{
	int ch;
	char line[100];

	// Ignore any blank lines
	while ((ch = fgetc(fp)) != EOF && isspace(ch));

	// Recursively ignore comments
	// in a PGM image commented lines
	// start with a '#'
	if (ch == '#') {
		fgets(line, sizeof(line), fp);
		proxLinhaDescomentada(fp);
	}
	else
		fseek(fp, -1, SEEK_CUR);
}


tImagemPGM *tratarImagem(FILE *fp)
{
    char *linha;
    int nLinhas = 0;
    size_t len = 0;
    size_t read;
    char tipo[5];
    char colunas[4];
    char linhas[5]; 

	proxLinhaDescomentada(fp);
	fscanf(fp, "%s",tipo);

    proxLinhaDescomentada(fp);
	// Read the image dimensions
	fscanf(fp, "%s %s",colunas,linhas);


    printf("tipo : %s", tipo); 
    printf("colunas  e linhas : %s %s", colunas,linhas); 

}

FILE *tratarImagemPorEntrada(char *entrada)
{
    FILE *fp = fopen(entrada, "rb");

    if (!fp || fp == NULL)
    {
        fprintf(stderr, RED "[ERRO]" NC ": Arquivo %s não existe \n"
                            "\n",
                entrada);
        exit(EXIT_FAILURE);
    }
    tratarImagem(fp);
    fclose(fp);
}

tImagemPGM *retornarImagemDeEntrada(char *entrada)
{
    tImagemPGM *imagemRecebida = malloc(sizeof(tImagemPGM));
    if (strlen(entrada) > 1)
    {
        tratarImagemPorEntrada(entrada);
    }else{
        tratarImagem(stdin);
    }

    //     typedef struct tImagemPGM {
    //           int linhas;
    //           int colunas;
    //           int max_cinza;
    //           int **matriz;
    //      } tImagemPGM;

    // tImagemPGM = imagem;

    // return imagemLida;
    return imagemRecebida;
}