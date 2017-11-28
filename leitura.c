#include "leitura.h"

void lerVert(char *linha, struct vertice *vert){

   char *x=strtok(linha," ");                               //separa até o espaço 
   char *y=strtok('\0'," ");
   char *z=strtok('\0',"  \n");

   x=strtok(x,"/");                                        //separa até a barra, se houver
   y=strtok(y,"/");
   z=strtok(z,"/");

   vert->x=atof(x);										   //converte para float
   vert->y=atof(y);
   vert->z=atof(z);
}

void lerFace(char *linha, struct face *f){
	char **aux=(char **)malloc(sizeof(char *));				
	aux[0]=strtok(linha," ");								
	int i=0;	
	while(aux[i]){
		i++;
		aux=(char **)realloc(aux,(i+1)*sizeof(char *));		//divide a string
		aux[i]=strtok('\0'," \n");
	}

	f->pontos=(int *)malloc(i*sizeof(int));
	f->nponts=i;

	for(int j=0; j<f->nponts; j++){						//pega a string antes da barra(se houver) e transforma em float
		aux[j]=strtok(aux[j],"/");
		f->pontos[j]=atof(aux[j]);
	}

}

char *freadL(FILE *arq, int *fim){
	char *linha;
	linha=(char *)malloc(sizeof(char));  //aloca uma posicão de memoria para um char

	int i=-1;
	do{	
		i++;
		linha=(char *)realloc(linha,(i+1)*sizeof(char)); //realoca a posicão de memoria +1 char a cada interação
		linha[i]=fgetc(arq);							 //pega o char do arquivo 
	}while((linha[i]!='\n')&&(linha[i]!=EOF));			 //enquanto é diferente de \n ou EOF
	
	if (linha[i]==EOF)									//se for EOF muda o fim para sair do while externo a essa função
		*fim=1;
		
	if ((linha[i]=='\n')&&(linha[i-1]=='x')&&(linha[i-2]==':')){ //se tiver a sequencia :x\n muda o fim e coloca o caracter nulo no lugar do :
		*fim=1;
		linha[i-2]='\0';
	}

	linha[i]='\0';		//INSERE O CARACTER NULO NO LUGAR DO \n 

	return linha;
}

char *readL(int *fim){
	char *linha;
	linha=(char *)malloc(sizeof(char));  //aloca uma posicão de memoria para um char

	int i=-1;
	do{	
		i++;
		linha=(char *)realloc(linha,(i+1)*sizeof(char)); //realoca a posicão de memoria +1 char a cada interação
		linha[i]=getchar( );							 //pega o char do arquivo 
	}while((linha[i]!='\n')&&(linha[i]!=EOF));			 //enquanto é diferente de \n ou EOF
	
	if (linha[i] == EOF)									//se for EOF muda o fim para sair do while externo a essa função
		*fim=1;
		
	if ((linha[i]=='\n')&&(linha[i-1]=='x')&&(linha[i-2]==':')){ //se tiver a sequencia :x\n muda o fim e coloca o caracter nulo no lugar do :
		*fim=1;
		linha[i-2]='\0';
	}

	linha[i]='\0';		//INSERE O CARACTER NULO NO LUGAR DO \n 

	return linha;
}


void lerObj(struct objeto *obj, FILE *arq){
	char *linha;
	obj->nvert=0;
	obj->nface=0;
	int fim=0;
		// obj->vertices=malloc(obj->nvert*sizeof(struct vertice));
		// obj->faces=malloc(obj->nvert*sizeof(struct vertice));
	while (!fim){
		linha=freadL(arq,&fim);
		if ((linha[0]=='v')&&(linha[1]==' ')){
			// obj->nvert++;
			// obj->vertices=(struct vertice *)realloc(obj->vertices,obj->nvert*sizeof(struct vertice));
			// lerVert(&linha[2],&obj->vertices[obj->nvert-1]);
		}else
		if ((linha[0]=='f')&&(linha[1]==' ')){
			// obj->nface++;
			// obj->faces=(struct face *)realloc(obj->faces,obj->nface*sizeof(struct face));
			// lerFace(&linha[2],&obj->faces[obj->nface-1]);
		}
	}
}



void lerObj_Stdin(struct objeto *obj){
	char *linha;
	obj->nvert=0;
	obj->nface=0;
	int fim=0;
	while (!fim){
		linha=readL(&fim);
		// printf("obj->nvert %d\n",obj->nvert );
		obj->nvert++;
		// printf("obj->nvert %d\n",obj->nvert );
		if ((linha[0]=='v')&&(linha[1]==' ')){
			obj->nvert++;
			obj->vertices=(struct vertice *)realloc(obj->vertices,obj->nvert*sizeof(struct vertice));
			lerVert(&linha[2],&obj->vertices[obj->nvert-1]);
		}
		else
		if ((linha[0]=='f')&&(linha[1]==' ')){
			obj->nface++;
			obj->faces=(struct face *)realloc(obj->faces,obj->nface*sizeof(struct face));
			lerFace(&linha[2],&obj->faces[obj->nface-1]);
		}
	}
}

void calcProj(struct objeto *obj,struct objeto *proj,struct cord_tela *ajust, struct vertice *cam){
	/*CALCULA PROJEÇÃO 2D DO OBJETO*/
	proj->vertices=malloc(obj->nvert*sizeof(struct vertice));
	for (int i =0; i<obj->nvert; i++){

		proj->vertices[i].x = (cam->x + cam->z) * (obj->vertices[i].x - cam->x) / (obj->vertices[i].z + cam->z); //Formula
		proj->vertices[i].y = (cam->y + cam->z) * (obj->vertices[i].y - cam->y) / (obj->vertices[i].z + cam->z); //Formula

		#ifdef PRINTINFOS
		printf("proj->vertices[%d].x:%f\n",i,proj->vertices[i].x );
		printf("proj->vertices[%d].y:%f\n",i,proj->vertices[i].y );
		#endif

		if (i==0)//primeira vez no laço associa o primeio x ao xmax, depois confere se existe algum maior 
		{
			ajust->xmax = proj->vertices[i].x;
			ajust->ymax = proj->vertices[i].y;

			ajust->xmin = proj->vertices[i].x;
			ajust->ymin = proj->vertices[i].y;
		}
		else{
			/*encontra max das coordenadas x e y*/
			if (proj->vertices[i].x > ajust->xmax)
				ajust->xmax = proj->vertices[i].x;
			if (proj->vertices[i].y > ajust->ymax)
				ajust->ymax = proj->vertices[i].y;

			/*encontra min das coordenadas x e y*/
			if (proj->vertices[i].x < ajust->xmin)
				ajust->xmin = proj->vertices[i].x;
			if (proj->vertices[i].y < ajust->ymin)
				ajust->ymin = proj->vertices[i].y;
		}
	}
	#ifdef PRINTINFOS
	printf("ajust->xmax: %f\n",ajust->xmax );
	printf("ajust->ymax: %f\n",ajust->ymax );
	#endif
					// //CALCULA ESCALA,CENTRO E DIFERENCA DAS COORDENADAS
	ajust->xcent = (ajust->xmax + ajust->xmin) / 2;
	ajust->ycent = (ajust->ymax + ajust->ymin) / 2;

	#ifdef PRINTINFOS
	printf("ajust->xcent: %f\n",ajust->xcent );
	printf("ajust->ycent: %f\n",ajust->ycent );
	#endif

	ajust->xdif = ajust->xmax - ajust->xmin;
	ajust->ydif = ajust->ymax - ajust->ymin;

	#ifdef PRINTINFOS
	printf("ajust->xdif: %f\n",ajust->xdif );
	printf("ajust->ydif: %f\n",ajust->ydif );
	#endif

	if ((WIDTH/ajust->xdif)>(HEIGHT/ajust->ydif))
		ajust->escala = HEIGHT/ajust->ydif;
	else 
		ajust->escala = WIDTH/ajust->xdif;

	#ifdef PRINTINFOS
	printf("ajust->escala: %f\n",ajust->escala );
	#endif

					/*POSICIONA OBJETO NO CENTRO DA TELA E APLICA ESCALA*/
	for(int i=0; i<obj->nvert; i++){
		proj->vertices[i].x = ((proj->vertices[i].x - ajust->xcent) *ajust->escala) + WIDTH  / 2; //Formula
		proj->vertices[i].y = ((proj->vertices[i].y - ajust->ycent) *ajust->escala) + HEIGHT / 2;	//Formula

		#ifdef PRINTINFOS
		printf("proj->vertices[%d].x:%f\n",i,proj->vertices[i].x );
		printf("proj->vertices[%d].y:%f\n",i,proj->vertices[i].y );
		#endif
	}
}