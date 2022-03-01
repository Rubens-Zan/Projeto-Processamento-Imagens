#include <stdio.h>
#include <stdlib.h>
#include "tratarEntrada.h"
#include "tratarImagens.h"
#include "acessoImagens.h"
#include "estruturas.h"


int main(int argc, char **argv){
        tComando *comando = (tComando *)malloc(sizeof(tComando));
    tratamentoEntrada(argc,argv,comando);
    tImagemPGM *imagem = malloc(sizeof(tImagemPGM));
    retornarImagemDeEntrada(comando->entrada,imagem); 
    filtroNegativo(imagem);
    imprimirImagem(imagem,comando->saida);
    free(imagem); 
    return 0;
}