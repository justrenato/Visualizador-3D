CFLAGS = -Wall -g -lSDL -lSDL_gfx -lm
CC = gcc
objects = graphics.o wireframe.o objread.o
principal = objread.c



all: $(objects)
# regras de ligação
wireframe: $(principal)
	gcc $(principal) -o wireframe $(CFLAGS)
	
 
# regras de compilação 
graphics.o: graphics.c graphics.h datatypes.h
	gcc -c graphics.c $(CFLAGS)	

wireframe.o:wireframe.c objread.h datatypes.h graphics.h
	gcc -c wireframe.c $(CFLAGS)	

objread.o:objread.c objread.h datatypes.h
	gcc -c objread.c $(CFLAGS)	

clean:
	-rm *.o
purge: clean
	-rm $(objects)