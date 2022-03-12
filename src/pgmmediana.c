#include <stdio.h>
#include <stdlib.h>
#include "tratarEntrada.h"
#include "acessoImagens.h"
#include "estruturas.h"
#include <math.h>

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int medianaVizinhos(tImagemPGM *imagem, int lin, int col,int mascara){
    int vizinhos[50]; 
    int nVizinhos=0; 
    int linhaAtual,colunaAtual,mediana,i,j; 
    int vizinhosMascara = floor(mascara/2); 

    // ignorando pixeis que nao tem todos os vizinhos
    if (lin - vizinhosMascara < 0 || lin + vizinhosMascara > imagem->linhas || col - vizinhosMascara < 0 || col + vizinhosMascara > imagem->colunas){
        return imagem->matrizPixeis[lin][col]; 
    }

    for (i=-vizinhosMascara;i<=vizinhosMascara;i++){
        linhaAtual=lin+i;

        if (linhaAtual >= 0 && linhaAtual < imagem->linhas){
            for(j=-vizinhosMascara;j<=vizinhosMascara;j++){
                colunaAtual=col+j;
                if (colunaAtual >= 0 && colunaAtual < imagem->colunas){
                    vizinhos[nVizinhos]=imagem->matrizPixeis[linhaAtual][colunaAtual];
                    nVizinhos++;
                }
            }
        }
    }

    qsort(vizinhos, nVizinhos, sizeof(int), cmpfunc);
  
    if (nVizinhos % 2 == 0){
        int n = ceil(nVizinhos/2);
        mediana = vizinhos[n];
    }else{
        mediana = vizinhos[nVizinhos/2];
    }

    return mediana; 
}

void filtroMediana(tImagemPGM *imagem, int mascara){
    int linhaAtual,colunaAtual; 
    for (linhaAtual=0; linhaAtual < imagem->linhas; linhaAtual++){
        for (colunaAtual=0; colunaAtual<imagem->colunas;colunaAtual++){
            imagem->matrizPixeis[linhaAtual][colunaAtual]=medianaVizinhos(imagem,linhaAtual,colunaAtual,mascara); 
        }
    } 
}

int main(int argc, char **argv){
    tComando *comando = (tComando *)malloc(sizeof(tComando));
    tratamentoEntrada(argc,argv,comando);
    tImagemPGM *imagem = malloc(sizeof(tImagemPGM));
    retornarImagemDeEntrada(comando->entrada,imagem); 
    filtroMediana(imagem, comando->mascara); 
    imprimirImagem(imagem,comando->saida);
    free(imagem); 
    free(comando);
    return 0;
}