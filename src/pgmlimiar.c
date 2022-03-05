#include <stdio.h>
#include <stdlib.h>
#include "tratarEntrada.h"
#include "tratarImagens.h"
#include "acessoImagens.h"
#include "estruturas.h"
#include <math.h>

int main(int argc, char **argv){
    tComando *comando = (tComando *)malloc(sizeof(tComando));
    tratamentoEntrada(argc,argv,comando);
    tImagemPGM *imagem = malloc(sizeof(tImagemPGM));
    retornarImagemDeEntrada(comando->entrada,imagem); 
    int limiar = comando->limiar * imagem->maxCinza; 
    filtroLimiar(limiar,imagem);
    imprimirImagem(imagem,comando->saida);
    free(imagem); 
    free(comando); 
    return 0;
}