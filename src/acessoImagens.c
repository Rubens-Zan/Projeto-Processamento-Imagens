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
#include "acessoImagens.h"

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
    proxLinhaDescomentada(fp);
	fscanf(fp, "%s",dest);
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

void retornarImagemDeEntrada(char *entrada, tImagemPGM *img){
    char tipo[4];
    
    int row,col, ch_int;
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

    while(getc(imagemP) != '\n');           
    while (getc(imagemP) == '#')             
    {
        while (getc(imagemP) != '\n');         
    }
    fseek(imagemP, -1, SEEK_CUR);           
    fscanf(imagemP,"%d", &((*img).colunas));
    fscanf(imagemP,"%d", &((*img).linhas));
    fscanf(imagemP,"%d", &((*img).maxVal));
    strcpy((*img).tipo, tipo); 
    img->matrizPixeis=alocarMatriz(img->linhas,img->colunas);


    if (strcmp(tipo, "P2") == 0){
       for (row=0; row < ( *img).linhas-1; row++){
            for (col=0; col< (*img).colunas; col++){
            fscanf(imagemP,"%d", &ch_int);
            (*img).matrizPixeis[row][col]=ch_int; 
            }
        }
    }else{
        while(getc(imagemP) != '\n');
        for (row=(*img).linhas-1; row >=0; row--){
            for (col=0; col< (*img).colunas; col++){
                (*img).matrizPixeis[row][col]=getc(imagemP); 
            }
        }
    }

    fecharImagem(imagemP);
}

void imprimirImagem(tImagemPGM *imagemTratada, char *saida){
    int i,j;
    FILE *imageout;  
    if (strcmp(saida,"padrao") == 0){
        imageout = stdout;
    }else {
        imageout = fopen(saida,"w");  
    }
    fprintf(imageout,"%s\n",imagemTratada->tipo);
    fprintf(imageout,"%d %d\n",  imagemTratada->colunas,imagemTratada->linhas); 
    fprintf(imageout,"%d\n", imagemTratada->maxVal);

    if (strcmp(imagemTratada->tipo, "P2") == 0){
        for ( i = 0; i < imagemTratada->linhas; i++){
            for (j=0; j<imagemTratada->colunas;j++){
                fprintf( imageout,"%d  " , imagemTratada->matrizPixeis[i][j]);
            } 
            fprintf( imageout,"\n" );
        }
    }else {
        for(i = imagemTratada->linhas - 1; i  >= 0; i--){
            for(j = 0; j <  imagemTratada->colunas; j++){
                putc(imagemTratada->matrizPixeis[i][j], imageout);

            }
        }
        fprintf(imageout, "\n");
    }

    fclose(imageout);
    free(imagemTratada->matrizPixeis[0]);
    free(imagemTratada->matrizPixeis);
}