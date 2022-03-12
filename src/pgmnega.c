#include <stdio.h>
#include <stdlib.h>
#include "tratarEntrada.h"
#include "acessoImagens.h"
#include "estruturas.h"

void filtroNegativo(tImagemPGM *imagem){
    int linhaAtual,colunaAtual; 
    for (linhaAtual=0; linhaAtual < imagem->linhas; linhaAtual++){
        for (colunaAtual=0; colunaAtual<imagem->colunas;colunaAtual++){
            imagem->matrizPixeis[linhaAtual][colunaAtual]=255-imagem->matrizPixeis[linhaAtual][colunaAtual]; 
        } 
    } 
}


int main(int argc, char **argv){
    tComando *comando = (tComando *)malloc(sizeof(tComando));
    tratamentoEntrada(argc,argv,comando);
    tImagemPGM *imagem = malloc(sizeof(tImagemPGM));
    retornarImagemDeEntrada(comando->entrada,imagem); 
    filtroNegativo(imagem);
    imprimirImagem(imagem,comando->saida);
    free(imagem); 
    free(comando); 
    return 0;
}