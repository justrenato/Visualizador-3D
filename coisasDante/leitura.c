#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <allegro5/allegro.h>

//gcc wireframe.c graphics.c -Wall -o teste -lSDL -lSDL_gfx -lm




typedef struct face{

  float x[50];
  float y[50];
  float z[50];
  float m[50];

  int cont;

}face;

typedef struct vertice{

  float x[50];
  float y[50];
  float z[50];


  int cont;

}vertice;



//testar as listas ou calloc

int main(int argc, char **argv)
{

  SDL_Init( SDL_INIT_EVERYTHING ); // precisa incializar essa função para carregar as demais
  SDL_Surface* off = NULL;
  SDL_Surface* in = NULL;

  Uint32 videoflags = SDL_SWSURFACE | SDL_SRCALPHA | SDL_RESIZABLE;

  off = SDL_SetVideoMode(800, 600, 32, videoflags);
  in = SDL_SetVideoMode(800, 600, 32, videoflags);



  //for(;;);






   FILE *arq ;

   arq = fopen(argv[1], "r") ;

   if ( ! arq )
   {
     perror ("Erro ao abrir arquivo x") ;
     exit (1) ; // encerra o programa com status 1
   }

   int cont;
   char ch;
   float x,y,z,m;

   face f;
   vertice v;

   f.cont = 0;
   v.cont = 0;


  while(!feof( arq ))
  {
        cont = fscanf(arq,"%c %f %f %f %f",&ch,&x,&y,&z,&m);

      if(cont==4&&ch=='v')
      {

      v.x[v.cont] = x;
      v.y[v.cont] = y;
      v.z[v.cont] = z;

      printf("LINHA DOS VERTICES %5.1f \t %5.1f \t %5.1f \t \n",v.x[v.cont],v.y[v.cont],v.z[v.cont]);

      v.cont++;
      }
      if(cont==5&&ch=='f')
      {
       f.x[f.cont] = (int)x;
       f.y[f.cont] = (int)y;
       f.z[f.cont] = (int)z;
       f.m[f.cont] = (int)m;

       printf("LINHA DAS FACES %5.1f \t %5.1f \t %5.1f \t %5.1f \t  \n",f.x[f.cont],f.y[f.cont],f.z[f.cont],f.m[f.cont]);

       f.cont++;
      }

  }

  fclose (arq) ;
   //exit (0) ;



  r2 rdois;

  rdois.x = malloc(sizeof(int)*v.cont);
  rdois.y = malloc(sizeof(int)*v.cont);

  camera view;


// isso aki vai ficar modificando


  view.x = 45;
  view.y = 50;
  view.z = 50;


  for(int k = 0;k < v.cont;k++)
  {
     rdois.x[k] = view.x + view.z*((v.x[k] - view.x)/(v.z[k] + view.z));
     rdois.y[k] = view.y + view.z*((v.y[k] - view.y)/(v.z[k] + view.z));
     if(k==0)
     {
      rdois.x_min = rdois.x[k];
      rdois.x_max = rdois.x[k];

      rdois.y_min = rdois.y[k];
      rdois.y_max = rdois.y[k];
     }
    if(rdois.x[k] > rdois.x_max )
      rdois.x_max = rdois.x[k];
    if(rdois.x[k] < rdois.x_min )
      rdois.x_min = rdois.x[k];

    if(rdois.y[k] > rdois.y_max )
      rdois.y_max = rdois.y[k];
    if(rdois.y[k] < rdois.y_min )
      rdois.y_min = rdois.y[k];


  }

  rdois.x_cen = (rdois.x_max + rdois.x_min)/2;
  rdois.x_dif = rdois.x_max - rdois.x_min;

  rdois.y_cen = (rdois.y_max + rdois.y_min)/2;
  rdois.y_dif = rdois.y_max - rdois.y_min;


  for(int k = 0;k < v.cont;k++)
  {
    printf("PONTOS OBTIDOS %5.1f %5.1f %d \n",rdois.x[k],rdois.y[k],k);
  }

  printf("minx e miny %5.1f %5.1f \n",rdois.x_min,rdois.y_min);
  printf("maxx e maxy %5.1f %5.1f \n",rdois.x_max,rdois.y_max);


  desenharnatela tela;

  tela.W = 640;
  tela.H = 480;

  tela.escala_x = tela.W/rdois.x_dif;
  tela.escala_y = tela.H/rdois.y_dif;


  if(tela.escala_x >= tela.escala_y )
  tela.escala = tela.escala_y;
  else
    tela.escala = tela.escala_x;


for(int k = 0;k < v.cont;k++)
  {
     rdois.x[k] = ((rdois.x[k]-rdois.x_cen)*tela.escala) + tela.W/2;
     rdois.y[k] = ((rdois.y[k]-rdois.y_cen)*tela.escala) + tela.H/2;

  }


 for(int k = 0;k < v.cont;k++)
  {
    printf("NOVOS PONTOS OVTIDOS %5.1f %5.1f %d \n",rdois.x[k],rdois.y[k],k);
  }


  //f.x = 1 , f.y = 2 , f.z = 3


  for(int k = 0;k < (f.cont - 1) ;k++)
  {
      //int k = 2;

      // k ==  ta dando problema com uma linha
      // analisar se o cast funciona
      int a,b,c,d;
      a = f.x[k]-1;// 1 ponto da  face
      b = f.y[k]-1;// 2 ponto da face
      c = f.z[k]-1;// terceiro ponto da face
      d = f.m[k]-1;// segundo ponto da FACES
      printf("tentativa de converter para int %d %d %d %d \n",a,b,c,d);

    lineRGBA(in,rdois.x[a],rdois.y[a],rdois.x[b],rdois.y[b],255,255,255,255); // blue
    lineRGBA(in,rdois.x[b],rdois.y[b],rdois.x[c],rdois.y[c],255,255,255,255); // green
    lineRGBA(in,rdois.x[c],rdois.y[c],rdois.x[d],rdois.y[d],255,255,255,255); // roxo
    lineRGBA(in,rdois.x[d],rdois.y[d],rdois.x[a],rdois.y[a],255,255,255,255); // red



    printf("testando os pontos em x a,b,c,d %5.1f %5.1f %5.1f %5.1f \n",rdois.x[a],rdois.x[b],rdois.x[c],rdois.x[d]);
    printf("testando os pontos em y a,b,c,d %5.1f %5.1f %5.1f %5.1f \n",rdois.y[a],rdois.y[b],rdois.y[c],rdois.y[d]);

  }




  //lineRGBA(in, 757.1, 514.3, 600.0, 471.4, 0, 255, 0, 255);

  //SDL_SetWindowPosition(off,5,5);


  SDL_BlitSurface( in, NULL, off, NULL );

  SDL_Flip( off );

  int derp;
  derp = 'q';
  while(derp == 'q')
    derp = getchar();




  return 0;

}





// typedef struct r2
// {

//   float *x;
//   float x_min;
//   float x_max;
//   float x_cen;
//   float x_dif;
//   float *y;
//   float y_min;
//   float y_max;
//   float y_cen;
//   float y_dif;

// }r2;



// //xp = xc + zc × ( (xv - xc) ÷ (zv + zc) )

// r2 espaço;

// espaço.x = malloc(sizeof(int)*vertice.cont);
// espaço.y = malloc(sizeof(int)*vertice.cont);


// x[k] = X_CAMERA + Z_CAMERA*((vertice.x[k] - (X_CAMERA))/vertice.z[k]+(Z_CAMERA))
// y[k] = Y_CAMERA + Z_CAMERA*((vertice.y[k] - (Y_CAMERA))/vertice.z[k]+(Z_CAMERA))

// //yp = yc + zc × ( (yv - yc) ÷ (zv + zc) )

// //Assim é obtida uma coleção de pontos [xp yp] que representa os vértices do objeto projetados no plano z=0.
