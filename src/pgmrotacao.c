#include <stdio.h>
#include <stdlib.h>
#include "tratarEntrada.h"
#include "acessoImagens.h"
#include "estruturas.h"
#include "bibliotecaGeral.h"
#include <math.h>

// gera um angulo em radiano de um angulo de grau
double radianos(double degrees) {
	return (degrees * M_PI) / 180;
}

void rotacao90Graus(tImagemPGM *imagem){
    int r, c;
    int linhas = imagem->linhas;
    int colunas = imagem->colunas;
    unsigned char **transposta=alocarMatriz(linhas,colunas); 

    for (r = 0; r < linhas; r++){
        for (c = 0; c < colunas; c++){            
            transposta[c][linhas-r-1]=imagem->matrizPixeis[r][c];
        }
    }

    copiarMatrizes(imagem->matrizPixeis,transposta, imagem->linhas, imagem->colunas); 
    free(transposta[0]);
    free(transposta);
}

void filtroRotacao(tImagemPGM *imagem, int angulo){
    // retornando em angulos que a imagem nao precisa ser rotacionada
    if (angulo == 0 || angulo % 360 == 0){
        return; 
    }
    // se o angulo for divisivel por 90, basta efetuar rotacoes simples
    if (angulo % 90 == 0){
        for (int i=0;i<angulo/90;i++){
            rotacao90Graus(imagem); 
        }
    }else{
        int x,y,velhaLargura,velhaAltura;
        velhaLargura = imagem->colunas;
        velhaAltura = imagem->linhas; 
        double sinA = fabs(sin(radianos(angulo)));
        double cosA = fabs(cos(radianos(angulo)));
        int novaAltura = sinA*velhaLargura+cosA*velhaAltura; 
        int novaLargura = cosA*velhaLargura+sinA*velhaAltura;
        unsigned char**rotacionada=alocarMatriz(novaAltura,novaLargura);

        for(x = 0; x < novaAltura; x++) {
        	for(y = 0; y < novaLargura; y++) {
                int ys = (int)((x * sin(radianos(angulo))) + (y * cos(radianos(angulo)))-(novaLargura-velhaLargura));
                int xs=(int)((x * cos(radianos(angulo))) - (y * sin(radianos(angulo))));
        		if(xs >= 0 && xs < velhaAltura && ys >= 0 && ys < velhaLargura) {
                    rotacionada[x][y]=imagem->matrizPixeis[xs][ys];
        		} else {
                    // setando para branco
                    rotacionada[x][y]=imagem->maxVal;
        		}
        	}
        }
        
        imagem->colunas=novaLargura;  
        imagem->linhas=novaAltura;
        free(imagem->matrizPixeis[0]);
        free(imagem->matrizPixeis);
        imagem->matrizPixeis=alocarMatriz(novaAltura,novaLargura);
        copiarMatrizes(imagem->matrizPixeis,rotacionada, novaAltura,novaLargura);
        free(rotacionada[0]);
        free(rotacionada); 
    }    
}

int main(int argc, char **argv){
    tComando *comando = (tComando *)malloc(sizeof(tComando));
    tratamentoEntrada(argc,argv,comando);
    tImagemPGM *imagem = malloc(sizeof(tImagemPGM));
    retornarImagemDeEntrada(comando->entrada,imagem); 
    filtroRotacao(imagem, comando->angulo);
    imprimirImagem(imagem,comando->saida);
    free(imagem); 
    free(comando); 
    return 0;
}