#include "estruturas.h"

#include <stdio.h>
#include <stdlib.h>

#define RED "\e[0;31m"
#define NC "\e[0m"

FILE *abrirImagem(char *entrada){
    FILE *imagem; 
    imagem = fopen(entrada, "r");

    if(!imagem || imagem == NULL){
        fprintf(stderr, RED "[ERRO]"
            NC  ": Arquivo %s não existe \n"
                "\n",entrada);
        exit(EXIT_FAILURE);
    }


    printf("LENDO IMAGEM"); 

    char ch = getc(imagem);
    if (ch != 'P'){
        printf("IMAGEM INVALIDA\n");
        exit(1);
    }
    
    fclose (imagem);
    exit(0); 
}

tImagemPGM *retornarImagemDeEntrada(char *entrada){
    FILE *imagemRecebida;
    if (entrada != NULL){
        imagemRecebida = abrirImagem(entrada); 
    }



//     typedef struct tImagemPGM {
//           int linhas;
//           int colunas;
//           int max_cinza;
//           int **matriz;
//      } tImagemPGM; 

    // tImagemPGM = imagem; 

    // return imagemLida; 
    return imagemRecebida; 
}