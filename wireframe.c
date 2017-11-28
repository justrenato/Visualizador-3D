#include "leitura.h"

// #define PRINTINFOS //n tirar essa caralha daqui plz ♥

int main(int argc, char* argv[]){
	struct objeto *obj=(struct objeto*)malloc(sizeof(struct objeto));
	struct objeto *proj=(struct objeto*)malloc(sizeof(struct objeto));

	/*Leitura do arquivo*/
	if(argc == 2){
		FILE *arq= fopen(argv[1],"r");
		if (arq == NULL) {
			printf("Arquivo \"%s\", não encontrado.\n",argv[1]);
			return -1;
		} 
		else lerObj(obj,arq); //leitura por argumento na linha de comando
	}
	else lerObj_Stdin(obj); //leitura por entrada padrão

	//inicia SDL
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface* window = SDL_SetVideoMode(WIDTH,HEIGHT,0, SDL_HWSURFACE | SDL_DOUBLEBUF);

    SDL_Event event;

	//inicia camera
	struct vertice cam;
	cam.x = 200;
	cam.y = 200;
	cam.z = 300;

	// struct objeto proj;
	struct cord_tela ajust;


	// LGBT ROSA (239, 2, 176)
	// lineRGBA (x1,y1,x2,y2,r,g,b,a)
    int sair=0;
    while (!sair){

    	/*tratar teclado hihi*/
    	while(SDL_PollEvent(&event)!=0){
    		SDL_PollEvent(&event);
    		if (event.type == SDL_QUIT) sair = 1;
    		else if(event.type == SDL_KEYDOWN){
    			switch(event.key.keysym.sym){
    				case SDLK_q:
    					sair =1;
    				break;
    				case SDLK_ESCAPE:
    					sair =1;
    				break;
    				case SDLK_UP:
    					cam.y++;
    				break;
    				case SDLK_DOWN:
    					cam.y--;
    				break;
    				case SDLK_RIGHT:
    					cam.x++;
    				break;
    				case SDLK_LEFT:
    					cam.x++;
    				break;

    				default: //se não tiver essa linha reclama que não ha "case" para as outras teclas do teclado
    				break;
    			}
    		}
    	}
	
		calcProj( obj,proj,&ajust,&cam);

		for (int i=0; i<obj->nface; i++){
			int tam = obj->faces[i].nponts;
			for (int j= 0; j<tam; j++){		
				int x1,x2,y1,y2;
				int ind = obj->faces[i].pontos[j];
				// 1ªcoordenada de um ponto da projeção
				if (j == tam-1){
					x1 = proj->vertices[ind-1].x;
					y1 = proj->vertices[ind-1].y;

					x2 = proj->vertices[0].x;
					y2 = proj->vertices[0].y;
				}
				else{
					x1 = proj->vertices[ind-1].x;
					y1 = proj->vertices[ind-1].y;   
					//2ªcoordenada  de um ponto da projeção 
					ind = obj->faces[i].pontos[j+1];

					x2 = proj->vertices[ind-1].x;
					y2 = proj->vertices[ind-1].y;
				}
				lineRGBA(window,x1,y1,x2,y2,239,2,176,101);
			}
		}

							/*EXEMPLOS*/
		// SDL_FillRect(window, NULL, SDL_MapRGB(window->format, 0, 0, 0));
		// pixelRGBA(window,10, 15,255, 255, 255, 255);
		// lineRGBA(window,20, 10,70, 90,255, 0, 0, 255);
		// trigonRGBA(window,500, 50,550, 200,600, 150,0, 255, 255, 255);
		// filledTrigonRGBA(window,200, 200,300, 50,400, 200,0, 0, 255, 255);
		// rectangleRGBA(window,-10, 300,100, 380,0, 255, 0, 255);
		// boxRGBA(window,210, 76,325, 300,255, 0, 0, 150);
		// ellipseRGBA(window,600, 400,50, 90,255, 255, 0, 200);
		// filledEllipseRGBA(window,600, 400,25, 150,0, 255, 0, 255);
		// short x[6] = { 350, 275, 300, 325, 350, 400 }; 
		// short y[6] = { 325, 325, 390, 390, 375, 300 };
		// polygonRGBA(window,x, y,6,255, 255, 255, 155);
		// short s[5] = { 400, 450, 450, 425, 300 }; 
		// short t[5] = { 400, 410, 450, 425, 500};
		// filledPolygonRGBA(window,s, t,5,255, 0, 255, 155);

		SDL_Flip(window);
    }

	/*PRINTA TUDO CHESUS*/
	// for (int i=0; i<obj->nvert; i++) //printa vertices
	// 	printf("v%d x:%f y:%f z:%f\n",i,obj->vertices[i].x,obj->vertices[i].y,obj->vertices[i].z);
	// printf("total de vertices: %d\n",obj->nvert );

	// for (int i=0; i<obj->nface; i++){//printa faces
	// 	printf("f %d ",i);
	// 	for (int j=0; j < obj->faces[i].nponts; j++){
	// 		printf("p%d: %d ",j,obj->faces[i].pontos[j]);
	// 	}
	// 	printf("\n");
	// }
    SDL_Quit();
	return 0;
}