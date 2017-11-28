#include <stdlib.h>
#include <stdio.h>
#include "graphics.h"
#include "datatypes.h"
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>


void controla_camera(CAMERA *camera,int x,int y,int z)
{
    camera->x = x;
    camera->y = y;
    camera->z = z;
}

void muda_r3_to_r2(VERTICE *vertice, R2VERTICE *r2vertice,CAMERA *camera)
{
    //escalas
    float escala_x,escala_y,escala;
    //tela
    float W,H;
    //coordenadas
    float x_min,y_min,x_cen,y_cen,y_max,x_max,x_dif,y_dif;
    //pontos da camera
    float x,y,z;
    x = camera->x;
    y = camera->y;
    z = camera->z;

    int tam = vertice->cont;


    // converte r2>>r3 , obtem os valores max e min
    for(int i = 0; i < tam; i++)
    {

        r2vertice->x[i] = x + z*((vertice->x[i] - x)/(vertice->z[i] + z));
        r2vertice->y[i] = y + z*((vertice->y[i] - y)/(vertice->z[i] + z));

        if(i==0)
        {
            x_min = r2vertice->x[i];
            x_max = r2vertice->x[i];
            y_min = r2vertice->y[i];
            y_max = r2vertice->y[i];
        }
        if(r2vertice->x[i] > x_max )
            x_max = r2vertice->x[i];
        if(r2vertice->x[i] < x_min )
            x_min = r2vertice->x[i];

        if(r2vertice->y[i] > y_max )
            y_max = r2vertice->y[i];
        if(r2vertice->y[i] < y_min )
            y_min = r2vertice->y[i];

    }



    x_cen = (x_max + x_min)/2;
    x_dif = x_max - x_min;

    y_cen = (y_max + y_min)/2;
    y_dif = y_max - y_min;


    //*************TAMANHO DA TELA QUE SERA PLOTADA *****************************//
    W = 800;
    H = 600;

    escala_x = W/x_dif;
    escala_y = H/y_dif;


    if(escala_x >= escala_y )
        escala = escala_y;
    else
        escala = escala_x;



    for(int i = 0; i < tam ; i++)
    {
        r2vertice->x[i] = ((r2vertice->x[i]-x_cen)*escala) + W/2;
        r2vertice->y[i] = -((r2vertice->y[i]-y_cen)*escala) + H/2;
    }




}

void draw(FACE *face,R2VERTICE *r2vertice,SDL_Surface *off,SDL_Surface *in)
{

   
    // após isso posso plotar na face in
    int jotalinha;

    for(int k = 0; k < face->cont; k++)
    {

        for(int j=0; j < face->tam[k]; j++)
        {
            jotalinha = (j+1) % face->tam[k];
            lineRGBA(in,r2vertice->x[(face->matriz[k][j]-1)],r2vertice->y[(face->matriz[k][j]-1)],r2vertice->x[(face->matriz[k][jotalinha]-1)],r2vertice->y[(face->matriz[k][jotalinha]-1)],255,255,255,100);

        }

    }


    //adiciona plotagem feita em in para off
    SDL_BlitSurface( in, NULL, off, NULL );

    SDL_Flip( off );

}
