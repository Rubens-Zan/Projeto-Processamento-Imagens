#include <stdio.h>
#include <stdlib.h>
#include "tratarEntrada.h"
#include "acessoImagens.h"
#include "estruturas.h"
#include <math.h>

void filtroLimiar(int limiar, tImagemPGM *imagem){
    int linhaAtual,colunaAtual; 
    for (linhaAtual=0; linhaAtual < imagem->linhas; linhaAtual++){
        for (colunaAtual=0; colunaAtual < imagem->colunas;colunaAtual++){
            if (imagem->matrizPixeis[linhaAtual][colunaAtual] > limiar){
                imagem->matrizPixeis[linhaAtual][colunaAtual]=imagem->maxVal;
            } else{
                imagem->matrizPixeis[linhaAtual][colunaAtual]=0;
            }
        } 
    }
}

int main(int argc, char **argv){
    tComando *comando = (tComando *)malloc(sizeof(tComando));
    tratamentoEntrada(argc,argv,comando);
    tImagemPGM *imagem = malloc(sizeof(tImagemPGM));
    retornarImagemDeEntrada(comando->entrada,imagem); 
    int limiar = comando->limiar * imagem->maxVal; 
    filtroLimiar(limiar,imagem);
    imprimirImagem(imagem,comando->saida);
    free(imagem); 
    free(comando); 
    return 0;
}