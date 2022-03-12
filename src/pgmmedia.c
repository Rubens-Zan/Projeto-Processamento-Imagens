#include <stdio.h>
#include <stdlib.h>
#include "tratarEntrada.h"
#include "acessoImagens.h"
#include "estruturas.h"

int mediaVizinhos(tImagemPGM *imagem, int lin,int col){
    int soma=0;
    int vizinhos=0; 
    int media,i,j,linAtual, colAtual; 
   
    for (i=-1;i<=1;i++){
        linAtual=lin+i;

        if (linAtual >= 0 && linAtual < imagem->linhas){
            for(j=-1;j<=1;j++){
                colAtual=col+j;
                if (colAtual >= 0 && colAtual < imagem->colunas){
                    soma+=imagem->matrizPixeis[linAtual][colAtual];
                    vizinhos++;     
                }
            }
        } 
    }
    
    media = soma / vizinhos; 
    return media; 
}


void filtroMedia(tImagemPGM *imagem){
    int linhaAtual,colunaAtual; 
    for (linhaAtual=0; linhaAtual < imagem->linhas; linhaAtual++){
        for (colunaAtual=0; colunaAtual < imagem->colunas;colunaAtual++){
            imagem->matrizPixeis[linhaAtual][colunaAtual]=mediaVizinhos(imagem,linhaAtual,colunaAtual);
        }
    } 
}


int main(int argc, char **argv){
    tComando *comando = (tComando *)malloc(sizeof(tComando));
    tratamentoEntrada(argc,argv,comando);
    tImagemPGM *imagem = malloc(sizeof(tImagemPGM));
    retornarImagemDeEntrada(comando->entrada,imagem);
    filtroMedia(imagem);
    imprimirImagem(imagem,comando->saida);
    free(imagem); 
    free(comando); 
    return 0;
}