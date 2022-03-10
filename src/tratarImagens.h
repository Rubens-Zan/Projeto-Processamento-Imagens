#include "estruturas.h"

void filtroLimiar(int limiar, tImagemPGM *imagem);
void filtroNegativo(tImagemPGM *imagem); 
void rotacaoSimples(tImagemPGM *imagem);
void filtroMedia(tImagemPGM *imagem); 
void filtroMediana(tImagemPGM *imagem, int mascara); 
int medianaVizinhos(tImagemPGM *imagem, int lin, int col,int mascara);
int mediaVizinhos(tImagemPGM *imagem, int lin,int col); 
void filtroLBP(tImagemPGM *imagem); 