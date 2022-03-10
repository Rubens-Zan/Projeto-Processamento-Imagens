# Makefile compilacao programa processamento de imagens
# Para efetuar a compilação digite make all
# Para remover os arquivos temporários digite make clean
# Para remover os arquivos temporários e o arquivo executável digite make purge

CFLAGS = -Wall -lm

MODULOS = tratarEntrada \
	tratarImagens \
	acessoImagens


OBJETOS = $(addsuffix .o,$(MODULOS)) 

ALVOS =  pgmlimiar pgmnega pgmmedia pgmmediana pgmrotacao pgmlbp 

.PHONY : all clean

all : $(ALVOS)

pgmlimiar: $(OBJETOS)
	gcc -o $@ $(OBJETOS) pgmlimiar.c $(CFLAGS)

pgmrotacao: $(OBJETOS)
	gcc -o $@ $(OBJETOS) pgmrotacao.c $(CFLAGS)

pgmmediana: $(OBJETOS) 
	gcc -o $@ $(OBJETOS) pgmmediana.c $(CFLAGS)

pgmmedia: $(OBJETOS)	 
	gcc -o $@ $(OBJETOS) pgmmedia.c $(CFLAGS)
	
pgmnega: $(OBJETOS)
	gcc -o $@ $(OBJETOS) pgmnega.c $(CFLAGS)

pgmlbp: $(OBJETOS)
	gcc -o $@ $(OBJETOS) pgmlbp.c $(CFLAGS)

clean : 
	$(RM) $(OBJETOS)

purge: 
	$(RM) $(OBJETOS) $(ALVOS)
