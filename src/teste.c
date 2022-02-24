#include <stdio.h>
#include <stdlib.h>
#include "tratarEntrada.h"
#include "tratarImagens.h"
#include "estruturas.h"

int main(int argc, char **argv){
    tComando *comandoTeste = tratamentoEntrada(argc,argv);
    tImagemPGM *imagem = malloc(sizeof(tImagemPGM));
    retornarImagemDeEntrada(comandoTeste->entrada,imagem); 
    imprimirImagem(imagem,comandoTeste->saida);
    return 0;
}