#include <stdio.h>
#include "tratarEntrada.h"
//#include "estruturas.h"

int main(int argc, char **argv){
    tComando *comandoTeste = tratamentoEntrada(argc,argv);

    printf("comandos %s %s %d %d %f\n", comandoTeste->entrada, comandoTeste->saida,comandoTeste->mascara, comandoTeste->angulo, comandoTeste->limiar); 
    return 0;
}
