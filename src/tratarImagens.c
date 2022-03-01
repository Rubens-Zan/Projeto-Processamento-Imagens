#include "tratarImagens.h"

void filtroLimiar(int limiar, tImagemPGM *imagem){
    int i,j; 
    for (i=0; i < imagem->linhas; i++){
        for (j=0; j<imagem->colunas;j++){
            if (*(imagem->matriz + i*imagem->colunas + j) > limiar){
                *(imagem->matriz + i*imagem->colunas + j)=imagem->maxCinza; 
            } else{
                *(imagem->matriz + i*imagem->colunas + j)=0; 
            }
        } 
    }
}

void filtroNegativo(tImagemPGM *imagem){
    int i,j; 
    for (i=0; i < imagem->linhas; i++){
        for (j=0; j<imagem->colunas;j++){
                *(imagem->matriz + i*imagem->colunas + j)=255-*(imagem->matriz + i*imagem->colunas + j); 
        } 
    } 
}

void filtroRotacaoSimples(tImagemPGM *imagem){
   int *matriz; 
   int i,j;

    for (i=0; i < imagem->linhas; i++){
        for (j=0; j<imagem->colunas;j++){
            *(matriz + i*imagem->colunas + j)=*(imagem->matriz + i*imagem->colunas + j); 
        } 
    } 

}