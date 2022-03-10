#include "tratarImagens.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void filtroLimiar(int limiar, tImagemPGM *imagem){
    int linhaAtual,colunaAtual; 
    for (linhaAtual=0; linhaAtual < imagem->linhas; linhaAtual++){
        for (colunaAtual=0; colunaAtual < imagem->colunas;colunaAtual++){
            if (*(imagem->matriz + linhaAtual*imagem->colunas + colunaAtual) > limiar){
                *(imagem->matriz + linhaAtual*imagem->colunas + colunaAtual)=imagem->maxCinza; 
            } else{
                *(imagem->matriz + linhaAtual*imagem->colunas + colunaAtual)=0; 
            }
        } 
    }
}

void filtroNegativo(tImagemPGM *imagem){
    int linhaAtual,colunaAtual; 
    for (linhaAtual=0; linhaAtual <= imagem->linhas; linhaAtual++){
        for (colunaAtual=0; colunaAtual<=imagem->colunas;colunaAtual++){
            *(imagem->matriz + linhaAtual*imagem->colunas + colunaAtual)=255-*(imagem->matriz + linhaAtual*imagem->colunas + colunaAtual); 
        } 
    } 
}

void filtroMedia(tImagemPGM *imagem){
    int linhaAtual,colunaAtual; 
    for (linhaAtual=0; linhaAtual < imagem->linhas; linhaAtual++){
        for (colunaAtual=0; colunaAtual < imagem->colunas;colunaAtual++){
            *(imagem->matriz + linhaAtual*imagem->colunas + colunaAtual)=mediaVizinhos(imagem,linhaAtual,colunaAtual); 
        }
    } 
}

void filtroMediana(tImagemPGM *imagem, int mascara){
    int linhaAtual,colunaAtual; 
    for (linhaAtual=0; linhaAtual < imagem->linhas; linhaAtual++){
        for (colunaAtual=0; colunaAtual<imagem->colunas;colunaAtual++){
            *(imagem->matriz + linhaAtual*imagem->colunas + colunaAtual)=medianaVizinhos(imagem,linhaAtual,colunaAtual,mascara); 
        }
    } 
}

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
        return *(imagem->matriz+lin*imagem->colunas+col);
    }

    for (i=-vizinhosMascara;i<=vizinhosMascara;i++){
        linhaAtual=lin+i;
        for(j=-vizinhosMascara;j<=vizinhosMascara;j++){
            colunaAtual=col+j;
            if (colunaAtual >= 0 && colunaAtual <= imagem->colunas){
                vizinhos[nVizinhos]=*(imagem->matriz+linhaAtual*imagem->colunas+colunaAtual);
                nVizinhos++;
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

int mediaVizinhos(tImagemPGM *imagem, int lin,int col){
    int soma=0;
    int vizinhos=0; 
    int media,i,j,linAtual, colAtual; 
   
    for (i=-1;i<=1;i++){
        linAtual=lin+i;

        if (linAtual >= 0 && linAtual < imagem->linhas){
            for(j=-1;j<=1;j++){
                colAtual=col+j;
                if (colAtual >= 0 && colAtual < imagem->colunas){
                    soma+=*(imagem->matriz+linAtual*imagem->colunas+colAtual);
                    vizinhos++;     
                }
            }
        } 
    }
    
    media = soma / vizinhos; 
    return media; 
}

void rotacaoSimples(tImagemPGM *imagem){
    int r, c;
    int linhas = imagem->linhas;
    int colunas = imagem->colunas;
    int *transposta=malloc(sizeof(int)*linhas*colunas);

    for (r = 0; r < linhas; r++){
        for (c = 0; c < colunas; c++){
            *(transposta + c * linhas + (linhas - r - 1)) = *(imagem->matriz + r * colunas + c);
        }
    }

    copiarMatrizes(imagem->matriz,transposta, imagem->linhas, imagem->colunas); 
    free(transposta); 
}

void filtroLBP(tImagemPGM *imagem){
    int vizinhosLBP[3][3] = {{1,2,4},{8,0,16},{32,64,128}};
    int nLinhas = imagem->linhas;
    int nColunas = imagem->colunas;
    int *matrizLBP=malloc(sizeof(int)*nLinhas*nColunas);
    int i, j, linAtual, colAtual,pixelCentral,pixelAtual,soma; 

    int lin,col; 
    for (lin=0; lin < imagem->linhas; lin++){
        for (col=0; col <imagem->colunas;col++){
            soma = 0;
            pixelCentral = *(imagem->matriz+lin*imagem->colunas+col);

            for (i=-1;i<=1;i++){
                linAtual=lin+i;

                if (linAtual >= 0 && linAtual < imagem->linhas){
                    for(j=-1;j<=1;j++){
                        colAtual=col+j;
                        if (colAtual >= 0 && colAtual < imagem->colunas){
                            pixelAtual=*(imagem->matriz+linAtual*imagem->colunas+colAtual);

                            if (pixelAtual > pixelCentral){
                                soma+=vizinhosLBP[i+1][j+1];
                            }
                        }
                    }
                } 
            }

            
        *(matrizLBP + lin*nColunas + col)=soma; 
        }
    } 

    copiarMatrizes(imagem->matriz,matrizLBP, imagem->linhas, imagem->colunas); 
    free(matrizLBP); 
}

void copiarMatrizes(int *matrizA, int *matrizB,int linhas,int colunas){
    int i,j; 
    for (i = 0; i < linhas; i++){
        for (j = 0; j < colunas;j++){
            *(matrizA + i*colunas + j)=*(matrizB + i*colunas + j); 
        }
    }
}