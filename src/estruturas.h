#ifndef _ESTRUTRAS_H_
#define _ESTRUTURAS_H_

typedef struct tComando {
    float limiar; 
    int angulo; 
    unsigned int mascara; 
    char saida[100];
    char entrada[100];
} tComando;

typedef struct imagemPGM {
    int linha;
    int coluna;
    int max_cinza;
    int **matriz;
} imagemPGM; 

#endif