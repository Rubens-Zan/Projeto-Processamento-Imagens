#include "bibliotecaGeral.h"
#include "acessoImagens.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

unsigned char ** alocarMatriz(int lin,int col){
    unsigned char **matriz;
    matriz = malloc(lin * sizeof(unsigned char*)); 
    matriz[0]=malloc(lin *col*sizeof(unsigned char));

    for (int i=1; i < lin; i++)
        matriz[i] = matriz[0] + i * col;

    return matriz; 
}

void liberarMatriz(unsigned char **matriz){
    free(matriz[0]);
    free(matriz);
}

void copiarMatrizes(unsigned char **matrizA, unsigned char **matrizB,int linhas,int colunas){
    int i,j; 
    for (i = 0; i < linhas; i++){
        for (j = 0; j < colunas;j++){
            matrizA[i][j]=matrizB[i][j]; 
        }
    }
}