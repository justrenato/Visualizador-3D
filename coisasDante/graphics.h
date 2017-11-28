
#ifndef __GRAPHICS__
#define __GRAPHICS__

#include "datatypes.h"
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>


typedef struct AUXILIAR{

  float x_min;
  float x_max;
  float x_cen;
  float x_dif;
  
  float y_min;
  float y_max;
  float y_cen;
  float y_dif;

  
  
  float escala_x;
  float escala_y;
  float escala;

}AUXILIAR;



void muda_r3_to_r2(VERTICE *vertice, R2VERTICE *r2vertice,CAMERA *camera);
void controla_camera(CAMERA *camera,int x,int y,int z);
void draw(FACE *face,R2VERTICE *r2vertice,SDL_Surface *off,SDL_Surface *in);




#endif