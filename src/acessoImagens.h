#ifndef _ACESSO_IMAGENS_H_
#define _ACESSO_IMAGENS_H_

#include "estruturas.h"

void imprimirImagem(tImagemPGM *imagemTratada, char *saida); 
void retornarImagemDeEntrada(char *entrada, tImagemPGM *img); 
unsigned char ** alocarMatriz(int lin,int col); 
void liberarMatriz(unsigned char **matriz); 

#endif