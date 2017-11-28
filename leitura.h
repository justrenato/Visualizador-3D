#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

#define SAIR   'q' || 27  //sair com q ou ESC
#define ESQ    'a'
#define DIR    'd'
#define CIM    'w'
#define BAIX   's'

#define WIDTH  800
#define HEIGHT 600

#define R      239
#define G      2
#define B      176

struct vertice{
	float x;
	float y;
	float z;
};

struct face{
	int *pontos;
	int nponts;
};


struct objeto{
	struct vertice *vertices;
	struct face *faces;
	float **arestas;
	int nvert;
	int nface;
};

struct cord_tela{
	float xmax;
	float ymax;
	
	float xmin;
	float ymin;
	
	float xcent;
	float ycent;
	
	float xdif;
	float ydif;

	float escala;
};

void lerVert(char *linha, struct vertice *vert);

void lerFace(char *linha, struct face *f);

char *freadL(FILE *arq, int *fim);

char *readL(int *fim);

void lerObj(struct objeto *obj, FILE *arq);

void lerObj_Stdin(struct objeto *obj);

void calcProj(struct objeto *obj,struct objeto *proj,struct cord_tela *ajust,struct vertice *cam);
