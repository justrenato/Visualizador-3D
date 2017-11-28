#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include "datatypes.h"
#include "graphics.h"

void cam_control(int x, int y, int z, CAM *cam){
	cam->x =x; cam->y =y; cam->z =z;
}
