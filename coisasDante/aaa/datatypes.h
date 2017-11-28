#ifndef __TYPES__
#define __TYPES__

typedef struc FACE{
	int **matrix; 
	// alocação dinamica, ponteiro pra ponteiros, guarda as infos do obj
	int *tamanho
	int num_faces;
}FACE;

typedef struct VERTICE{
	float *x,*y,*z;
	int num_faces;
}VERTICE;

typedef struct VERTICE_2{
	float *x, *y;
	int num_faces;
}VERTICE_2;

typedef struct CAM{
	float x,y,z;
}CAM;

typedef struct AUX{
	float x_min,x_max,x_centro,x;
	float y_min,y_max,y_centro,y;
	float e_x,e_y,e; //escala
}AUX;

#endif
