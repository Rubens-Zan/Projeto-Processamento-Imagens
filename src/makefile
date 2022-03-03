# Makefile compilacao programa processamento de imagens
# Para efetuar a compilação digite make all
# Para remover os arquivos temporários digite make clean
# Para remover os arquivos temporários e o arquivo executável digite make purge

CFLAGS = -Wall

MODULOS = tratarEntrada \
	tratarImagens \
	acessoImagens


OBJETOS = $(addsuffix .o,$(MODULOS)) 

.PHONY : all clean

all : pgmlimiar pgmnega pgmmedia pgmmediana pgmrotacao

pgmlimiar: $(OBJETOS)
	gcc $(CFLAGS) -o $@ $(OBJETOS) pgmlimiar.c

pgmrotacao: $(OBJETOS)
	gcc $(CFLAGS) -o $@ $(OBJETOS) pgmrotacao.c

pgmmediana: $(OBJETOS) 
	gcc $(CFLAGS) -o $@ $(OBJETOS) pgmmediana.c

pgmmedia: $(OBJETOS)	
	gcc $(CFLAGS) -o $@ $(OBJETOS) pgmmedia.c
	
pgmnega: $(OBJETOS)
	gcc $(CFLAGS) -o $@ $(OBJETOS) pgmnega.c

clean : 
	$(RM) $(OBJETOS)

purge: 
	$(RM) $(OBJETOS) pgmlimiar pgmnega pgmmedia pgmmediana pgmmmedia pgmrotacao
