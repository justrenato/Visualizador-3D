CFLAGS = -Wall -g
LFLAGS = -lSDL -lSDL_gfx -lm

objetos = wireframe.o leitura.o 

all: wireframe

wireframe: $(objetos)
	gcc -o wireframe $(objetos) $(LFLAGS)

wireframe.o: wireframe.c
	gcc -c wireframe.c $(CFLAGS)

leitura.o: leitura.c leitura.h
	gcc -c leitura.c $(CFLAGS)

# remove arquivos temporários
clean:
	-rm $(objetos)

# remove tudo o que não for o código-fonte original
purge: clean
	-rm wireframe