#ifndef __GRAPHICS__
#define __GRAPHICS__

#include "datatypes.h"

void cam_control(int x, int y, int z, CAM *cam);
void r3_r2(VERTICE *vertice, VERTICE_2 *vertice_2, CAM *cam);
void desenha(SDL *one, SDL *two, FACE *face, VERTICE_2 *vertice_2);

#endif