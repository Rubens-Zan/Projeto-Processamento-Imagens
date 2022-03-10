# Makefile compilacao programa processamento de imagens
# Para efetuar a compilação digite make all
# Para remover os arquivos temporários digite make clean
# Para remover os arquivos temporários e o arquivo executável digite make purge

CFLAGS = -Wall

MODULOS = tratarEntrada \
	tratarImagens \
	acessoImagens


OBJETOS = $(addsuffix .o,$(MODULOS)) 

ALVOS =  pgmlimiar pgmnega pgmmedia pgmmediana pgmrotacao pgmlbp 

.PHONY : all clean

all : $(ALVOS)

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

pgmlbp: $(OBJETOS)
	gcc $(CFLAGS) -o $@ $(OBJETOS) pgmlbp.c

clean : 
	$(RM) $(OBJETOS)

purge: 
	$(RM) $(OBJETOS) $(ALVOS)
