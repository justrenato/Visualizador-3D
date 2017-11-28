
#ifndef __DATATYPES__
#define __DATATYPES__



typedef struct FACE
{

    int **matriz; // precisa ser uma matriz para fazer malloc no momento que ler os numeros
    int *tam; // tam vai receber a quantidade de numeros lido assim fazemos o malloc do elemento da matriz


    int cont;//numero de faces

} FACE;

typedef struct VERTICE
{
    // pontos dos vertices
    float *x;
    float *y;
    float *z;

    int cont;

} VERTICE;

typedef struct R2VERTICE
{
    // converte r3 to r2
    float *x;
    float *y;

    int cont;
} R2VERTICE;


typedef struct CAMERA
{
    float x;
    float y;
    float z;

} CAMERA;






#endif
