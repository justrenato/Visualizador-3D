#include <stdio.h>
#include <stdlib.h>
#include "objread.h"
#include "datatypes.h"
#include "graphics.h"
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>






int main(int argc, char **argv)
{

    FACE *face;
    VERTICE *vertice;
    R2VERTICE *r2vertice;
    CAMERA *camera;


    int x,y,z,tam,quit;

    // posição inical da camera
    x = 100;
    y = 100;
    z = 100;




    //dedicado aos valores da face
    face = malloc(sizeof(FACE));
    //dedicado aos valores do vértice
    vertice = malloc(sizeof(VERTICE));
    //dedicado ao valor r3>>r2
    r2vertice = malloc(sizeof(R2VERTICE));
    //controla a posição da camera
    camera = malloc(sizeof(CAMERA));
    
    // adiciona elemento e retorna quantidade dos vértices
    tam = adiciona_elementos(face,vertice,argv[1]);

    r2vertice->x = malloc(sizeof(int)*tam);
    r2vertice->y = malloc(sizeof(int)*tam);



    //INICIALIZA SDL --------------------------------------------------------//
    SDL_Init( SDL_INIT_VIDEO ); // precisa incializar essa função para carregar as demais
    SDL_Surface* off = NULL; // face de display
    off = malloc(sizeof(SDL_Surface));
    SDL_Surface* in = NULL; // face que sera usada para plotar as linhas
    in = malloc(sizeof(SDL_Surface));
    Uint32 videoflags = SDL_SWSURFACE | SDL_SRCALPHA | SDL_RESIZABLE;
    off = SDL_SetVideoMode(800, 600, 0, videoflags);
    in = SDL_SetVideoMode(800, 600, 0, videoflags);
    //INICIALIZA SDL --------------------------------------------------------//



    //função de camera
    controla_camera(camera,x,y,z);
    //após a camera ser modificada chama-se r3>>r2
    muda_r3_to_r2(vertice,r2vertice,camera);
    //plotagem
    draw(face,r2vertice,off,in);    
  

        SDL_Delay(1000);

       

    
	


    //libera memória alocada dinamicamente 
    free(face);
    free(r2vertice);
    free(vertice);




    return 0;
}

