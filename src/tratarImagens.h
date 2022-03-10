#include "estruturas.h"

void filtroLimiar(int limiar, tImagemPGM *imagem);
void filtroNegativo(tImagemPGM *imagem);
void filtroRotacao(tImagemPGM *imagem, int angulo);  
void rotacao90Graus(tImagemPGM *imagem);
void filtroMedia(tImagemPGM *imagem); 
void filtroMediana(tImagemPGM *imagem, int mascara); 
int medianaVizinhos(tImagemPGM *imagem, int lin, int col,int mascara);
int mediaVizinhos(tImagemPGM *imagem, int lin,int col); 
void filtroLBP(tImagemPGM *imagem); 
void copiarMatrizes(int *matrizA, int *matrizB,int linhas,int colunas); 