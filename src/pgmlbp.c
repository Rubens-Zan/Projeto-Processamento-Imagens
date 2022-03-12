#include <stdio.h>
#include <stdlib.h>
#include "tratarEntrada.h"
#include "acessoImagens.h"
#include "estruturas.h"
#include "bibliotecaGeral.h"
#include <math.h>

void filtroLBP(tImagemPGM *imagem){
    int vizinhosLBP[3][3] = {{1,2,4},{8,0,16},{32,64,128}};
    int nLinhas = imagem->linhas;
    int nColunas = imagem->colunas;
    unsigned char **matrizLBP=alocarMatriz(nLinhas,nColunas);
    int i, j, linAtual, colAtual,pixelCentral,pixelAtual,soma; 

    int lin,col; 
    for (lin=0; lin < imagem->linhas; lin++){
        for (col=0; col <imagem->colunas;col++){
            soma = 0;
            pixelCentral = imagem->matrizPixeis[lin][col];

            for (i=-1;i<=1;i++){
                linAtual=lin+i;

                if (linAtual >= 0 && linAtual < imagem->linhas){
                    for(j=-1;j<=1;j++){
                        colAtual=col+j;
                        if (colAtual >= 0 && colAtual < imagem->colunas){
                            pixelAtual=imagem->matrizPixeis[linAtual][colAtual];
                            if (pixelAtual > pixelCentral){
                                soma+=vizinhosLBP[i+1][j+1];
                            }
                        }
                    }
                } 
            }

            matrizLBP[lin][col]=soma; 
        }
    } 

    copiarMatrizes(imagem->matrizPixeis,matrizLBP, imagem->linhas, imagem->colunas); 
    free(matrizLBP[0]);
    free(matrizLBP); 
}


int main(int argc, char **argv){
    tComando *comando = (tComando *)malloc(sizeof(tComando));
    tratamentoEntrada(argc,argv,comando);
    tImagemPGM *imagem = malloc(sizeof(tImagemPGM));
    retornarImagemDeEntrada(comando->entrada,imagem); 
    filtroLBP(imagem);
    imprimirImagem(imagem,comando->saida);
    free(imagem); 
    free(comando); 
    return 0;
}