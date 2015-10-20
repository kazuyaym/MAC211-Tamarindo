#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "superficie.h"
#include "inimigo.h"
#include <math.h>

#define LARGURA_TELA 800
#define ALTURA_TELA 600

inimigo INIMIGOinicializa(int id){
	inimigo coringa = malloc(sizeof(struct monstrinho));
	
	coringa->id = id;
	coringa->direcao = 0;
	coringa->xVel = 0; coringa->yVel = 0;
	coringa->x0 = 0; coringa->y0 = 0;
	coringa -> xInf = 0;
	coringa -> xSup = 800;
	coringa -> yInf = 0;
	coringa -> ySup = 600;
	
	switch(id){
		case 0:  coringa->box.w = 40;  coringa->box.h = 44;  break;
		case 1:  coringa->box.w = 28;  coringa->box.h = 21;  break;
		case 2:  coringa->box.w = 30;  coringa->box.h = 29;  break;
		case 3:	 coringa->box.w = 69;  coringa->box.h = 64;  break;
		case 4:  coringa->box.w = 98;  coringa->box.h = 58;  break;
		case 5:  coringa->box.w = 73;  coringa->box.h = 77;  break;
		case 6:  coringa->box.w = 119; coringa->box.h = 97;  break;
		case 7:	 coringa->box.w = 199; coringa->box.h = 137; break;
		case 8:  coringa->box.w = 98;  coringa->box.h = 69;  break;
		case 9:  coringa->box.w = 131; coringa->box.h = 156; break;
		case 10: coringa->box.w = 139; coringa->box.h = 137; break;
		case 11: coringa->box.w = 54;  coringa->box.h = 54;  break;
		case 12: coringa->box.w = 175; coringa->box.h = 207; break;
		case 13: coringa->box.w = 200; coringa->box.h = 98;  break;
		case 14: coringa->box.w = 208; coringa->box.h = 69;  break;
	}
	return coringa;
}

void INIMIGOmove_fantasma(inimigo coringa){
		/* Centro do circulo  
		-> x0; -> y0;
			
		-> xInf; velocidade
		-> xSup; raio 
		
		quadrante inicial e lado que irá girar
		-> yInf; -> ySup;
		*/
		
	coringa->xVel +=  0.01*coringa -> xInf;
	coringa->yVel +=  0.01*coringa -> xInf;
	
	coringa->box.x = coringa->x0 + coringa->yInf*coringa->xSup*sin(coringa->xVel);
	coringa->box.y = coringa->y0 + coringa->ySup*coringa->xSup*cos(coringa->yVel);
	
	if(coringa->xVel >= 6.28){
		coringa->yVel = coringa->yVel - 6.28;
		coringa->xVel = coringa->xVel - 6.28;
	}
}

void INIMIGOmove_tubarao(inimigo coringa){
	
	coringa->box.x += (coringa -> xVel? coringa->x0*coringa->box.w / coringa -> xVel : 0);
	coringa->box.y += (coringa -> yVel? coringa->y0*coringa->box.h / coringa -> yVel : 0);
	
	if(coringa -> xVel && coringa -> yVel){
		if( coringa->box.y > coringa-> ySup || coringa->box.y < coringa-> yInf){
			coringa->y0 *= -1; coringa->x0 *= -1;
		}
	}
	else{
		if( coringa->box.x > coringa-> xSup ) coringa->x0 = -1;
		if(	coringa->box.x < coringa-> xInf ) coringa->x0 = 1;
		if( coringa->box.y > coringa-> ySup ) coringa->y0 = -1; 
		if(	coringa->box.y < coringa-> yInf ) coringa->y0 = 1;
	}
}

void INIMIGOmove_bomba(inimigo coringa){
	if(coringa->xVel != 0) coringa->box.x += (coringa->xVel)*coringa->box.w / 3;
	if(coringa->yVel != 0) coringa->box.y += (coringa->yVel)*coringa->box.h / 3;
	
	if(coringa->box.x > coringa-> xSup || coringa->box.x < coringa-> xInf) coringa->box.x = coringa->x0;
	if(coringa->box.y > coringa-> ySup || coringa->box.y < coringa-> yInf) coringa->box.y = coringa->y0;

}

void INIMIGOmove_fogo(inimigo coringa){
	coringa->ySup++;
	if( coringa->ySup == 30 ) {
		coringa->ySup = -30;
		coringa->box.x = coringa->x0;
		coringa->box.y = coringa->y0;
	}
	if( coringa->ySup == 0 ){
		coringa->box.x = 800;
		coringa->box.y = 600;
	}
}

void INIMIGOmove(inimigo coringa){
	switch(coringa->id){
		case 0: INIMIGOmove_fantasma(coringa); break;
		case 1: INIMIGOmove_tubarao(coringa); break;
		case 2: INIMIGOmove_bomba(coringa); break;
		case 13: INIMIGOmove_fogo(coringa); break;
		case 14: INIMIGOmove_fogo(coringa); break;
	}
}

void INIMIGOshow(inimigo coringa, SDL_Surface* SUPERFICIEinimigo, SDL_Surface* tela) {
    /* Mostra o inimigo */
    aplica_superficie( coringa->box.x, coringa->box.y, SUPERFICIEinimigo, tela, NULL );
}
