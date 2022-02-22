#include "estruturas.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define RED "\e[0;31m"
#define NC "\e[0m"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tratarImagens.h"

void proxLinhaDescomentada(FILE* fp){
	int ch;
	char line[100];

	// Ignorando linhas nao relevantes
	while ((ch = fgetc(fp)) != EOF && isspace(ch));
	if (ch == '#') {
		fgets(line, sizeof(line), fp);
		proxLinhaDescomentada(fp);
	}
	else
		fseek(fp, -1, SEEK_CUR);
}

void copiarProxLinhaValida(FILE *fp, char *dest){
	char info[15];
    proxLinhaDescomentada(fp);
	fscanf(fp, "%s",dest);
}

tImagemPGM *tratarImagem(FILE *fp){
    char *linha;
    int nLinhas = 0;
    size_t len = 0;
    size_t read;
    char tipo[5];
    char colunas[4];
    char linhas[5]; 
    char maxCinza[4];

	proxLinhaDescomentada(fp);
	fscanf(fp, "%s",tipo);

    proxLinhaDescomentada(fp);
	// Read the image dimensions
	fscanf(fp, "%s",colunas);
	fscanf(fp, "%s",linhas);

    proxLinhaDescomentada(fp);
	fscanf(fp, "%s", maxCinza);
    proxLinhaDescomentada(fp);

    printf("tipo : %s\n", tipo); 
    printf("colunas  e linhas : %s %s\n", colunas,linhas); 
    printf("max cinza : %s\n", maxCinza); 
}

FILE *abrirImagem(char *entrada){
    FILE *fp = fopen(entrada, "rb");

    if (!fp || fp == NULL)
    {
        fprintf(stderr, RED "[ERRO]" NC ": Arquivo %s não existe \n"
                            "\n",
                entrada);
        exit(EXIT_FAILURE);
    }
    return fp;
}

void fecharImagem(FILE *fp){
    fclose(fp);
}

tImagemPGM *retornarImagemDeEntrada(char *entrada){
    char tipo[4];
    char colunas[5];
    char linhas[5];
    char maxCinza[4];
    
    FILE *imagemP;

    if (strcmp(entrada, "padrao") != 0){
        imagemP = abrirImagem(entrada);
    }else{
        imagemP = stdin;
    }

    copiarProxLinhaValida(imagemP, tipo);
    if (!(strcmp(tipo, "P5") == 0 || strcmp(tipo, "P2") == 0)) {
		fprintf(stderr,
				"Wrong file type!\n");
		exit(EXIT_FAILURE);
	}

    copiarProxLinhaValida(imagemP, colunas);
    copiarProxLinhaValida(imagemP, linhas);
    copiarProxLinhaValida(imagemP, maxCinza);

    tImagemPGM *imagemRecebida = malloc(sizeof(tImagemPGM));
    
    // alocando espaco para n linhas
    imagemRecebida->matriz = malloc(atoi(linhas) * sizeof(int));

    strcpy(imagemRecebida->tipo, tipo); 
    imagemRecebida->colunas=atoi(colunas);
    imagemRecebida->linhas=atoi(linhas); 
    imagemRecebida->maxCinza=atoi(maxCinza);

    int row,col, ch_int;
    for (row=0; row < imagemRecebida->linhas; row++){
        imagemRecebida->matriz[row]= malloc(imagemRecebida->colunas * sizeof(int));
        for (col=0; col < imagemRecebida->colunas; col++)
        {
            fscanf(imagemP,"%d", &ch_int);
            imagemRecebida->matriz[row][col] = ch_int;
        }
    }

    fecharImagem(imagemP);

    //     typedef struct tImagemPGM {
    //           int linhas;
    //           int colunas;
    //           int max_cinza;
    //           int **matriz;
    //      } tImagemPGM;

    // tImagemPGM = imagem;

    // return imagemLida;


    imprimirImagem(imagemRecebida, "./testeopa.pgm"); 
    return imagemRecebida;
}


void imprimirImagem(tImagemPGM *imagemTratada, char *saida){

    FILE *imageout = fopen(saida,"w+");
    int i,j;

    fprintf(imageout,"%s\n",imagemTratada->tipo);
    fprintf(imageout,"%d %d\n",  imagemTratada->colunas,imagemTratada->linhas); 
    fprintf(imageout,"%d\n", imagemTratada->maxCinza);

//--- CHANGED ------ Start
    for ( i = 0; i < imagemTratada->linhas; i++ )
    {
        for (j=0; j<imagemTratada->colunas;j++ )
        {
            fprintf( imageout,"%d  " , imagemTratada->matriz[i][j] );
        } 
            fprintf( imageout,"\n" );
    }

    fclose(imageout);

    free(imagemTratada);
}