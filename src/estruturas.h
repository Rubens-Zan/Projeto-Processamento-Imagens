#ifndef _ESTRUTURAS_H_
#define _ESTRUTURAS_H_

typedef struct tComando {
    float limiar; 
    int angulo; 
    unsigned int mascara; 
    char saida[100];
    char entrada[100];
} tComando;

typedef struct tImagemPGM {
    int linhas;
    int colunas;
    int maxVal;
    int *matriz;
    char tipo[4]; 
} tImagemPGM; 

#endif