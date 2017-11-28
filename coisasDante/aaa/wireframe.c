#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include "objread.h"
#include "datatypes.h"
#include "graphics.h"

int main(int argc, char const *argv[]){


//-------------------- INICIAÇÕES DO OBJETO ----------------------------------//	
	// apontam para structs que guardam info sobre os objetos aaa
	FACE *face;
	VERTICE *vertice;
	// converte os valores do R3 pro R2 a a a 
	VERTICE_2 *vertice_2;
	CAM *cam;

	//diz aonde vai estar a posição inical da câmera
	int x =100;
	int y =100;
	int z =100;

	face = malloc (sizeof(FACE));
	vertice = malloc (sizeof(VERTICE));
	vertice_2 = malloc (sizeof(VERTICE_2));
	cam = malloc(sizeof(CAM));

	int tamanho;
	// tamanho recebe a quantidade de vertices do objeto lido
	tamanho = objeto (face,vertice, argv[1]);

	vertice_2->x = (tamanho * sizeof(float));
	vertice_2->y = malloc(tamanho* sizeof(float));
	
//-------------------- INICIAÇÕES DO OBJETO ----------------------------------//	



//------------------------- INICIAÇÃO SDL ------------------------------------//

SDL_Init( SDL_INIT_VIDEO);
// inicia definitivamente o sdl
SDL *one = NULL;
SDL *two = NULL;

one = malloc(sizeof(SDL));
two =  malloc(sizeof(SDL));

Uint32 videoflags = SDL_SWSURFACE | SDL_SRCALPHA | SDL_RESIZABLE;
one = SDL_SetVideoMode(800,600,0,videoflags);
two = SDL_SetVideoMode(800,600,0,videoflags);


//------------------------- INICIAÇÃO SDL ------------------------------------//


//------------------------------ CAMERA ---------------------------------------//

cam_control(x, y, z, cam);
r3_r2(vertice, vertice_2, cam);
desenha(one, two,face, vertice_2);
SDL_Delay(500);

//------------------------------ CAMERA ---------------------------------------//


//--------------------------------FREE----------------------------------------//
freeee(face,vertice,vertice_2);

//--------------------------------FREE----------------------------------------//

return 0;
}