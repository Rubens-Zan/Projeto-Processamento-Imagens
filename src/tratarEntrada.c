#include "estruturas.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

#define RED "\e[0;31m"
#define NC "\e[0m"

void construaComando(char *entrada,char *saida, int mascara, int angulo,float limiar, tComando *comando){
    strcpy(comando->entrada, entrada);
    strcpy(comando->saida, saida);
    comando->angulo = angulo;
    comando->limiar = limiar;
    comando->mascara = mascara;
}

int valorEhValido(int type, char* recebido){
    int i;

    // checa se o valor recebido eh um inteiro
    if (type == 0){
        for (i=0;i<strlen(recebido);i++)
            if (!isdigit(recebido[i])){
                fprintf(stderr, RED "[ERROR]"
                    NC  ": Flag recebida é inválida %s \n"
                        "Você deve fornecer as flags com dígitos\n",recebido);
                exit(EXIT_FAILURE);
            }
    }

    return 1; 
}

void tratamentoEntrada(int argc, char **argv, tComando *comando){
    int i;
    
    // flags com valores default
    char saida[100]="padrao";
    char entrada[100]="padrao"; 
    unsigned int mascara = 3; 
    float limiar = 0.5; 
    int angulo = 90; 

    for (i=0;i<argc;i++){
        if (strcmp ( argv[i], "-i") == 0 && (i+1 < argc)){
            strcpy(entrada, argv[i+1]);
            i++; 
        }else if (strcmp ( argv[i], "-o") == 0 && (i+1 < argc)){
           strcpy(saida, argv[i+1]);
           i++;
        }else if (strcmp ( argv[i], "-a") == 0 && (i+1 < argc)){
            if (valorEhValido(0,argv[i+1])){
                angulo = atoi(argv[i+1]); 
                i++;
            }
        }else if(strcmp ( argv[i], "-m") == 0 && (i+1 < argc)){
            if (valorEhValido(0,argv[i+1])){
                mascara = atoi(argv[i+1]);
                i++;
            }
        }else if(strcmp ( argv[i], "-l") == 0 && (i+1 < argc)){
            if (valorEhValido(1,argv[i+1])){
                limiar = atof(argv[i+1]);
                i++;
            }
        }
    }

    construaComando(entrada,saida,mascara,angulo,limiar, comando);
}