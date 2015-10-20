#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "superficie.h"
#include "mapa.h"
#include "inimigo.h"
#include "barco.h"


#define LARGURA_TELA 800
#define ALTURA_TELA 600

#define LARGURA_BARCO 50
#define ALTURA_BARCO 50

#define VEL_MAX 8

#define boolean int
#define true 1
#define false 0

/* conjunto de Sprite do barco */
SDL_Rect SPRITEbarco[8];
int contador = 0;

barco BARCOinicializa() {
	barco titanic = malloc(sizeof(struct barquinho));
	
	titanic->vida = 0;
	/* Inicializa as velocidades */
	titanic->xVel = 0;
	titanic->yVel = 0;
	
	/* Inicia direcao do barco */
	titanic->direcao = 2;
	titanic->rotacao = 0;
	
	titanic->anda = 0;
	
	titanic->box.w = ALTURA_BARCO-10;
	titanic->box.h = LARGURA_BARCO-10;
	
	//leste
    SPRITEbarco[ 0 ].x = 0;
    SPRITEbarco[ 0 ].y = 0;
    SPRITEbarco[ 0 ].w = 50;
    SPRITEbarco[ 0 ].h = 50;

    //nordeste
    SPRITEbarco[ 1 ].x = 0;
    SPRITEbarco[ 1 ].y = 100;
    SPRITEbarco[ 1 ].w = 50;
    SPRITEbarco[ 1 ].h = 50;

    //norte
    SPRITEbarco[ 2 ].x = 0;
    SPRITEbarco[ 2 ].y = 50;
    SPRITEbarco[ 2 ].w = 50;
    SPRITEbarco[ 2 ].h = 50;

    //noroeste
    SPRITEbarco[ 3 ].x = 0;
    SPRITEbarco[ 3 ].y = 150;
    SPRITEbarco[ 3 ].w = 50;
    SPRITEbarco[ 3 ].h = 50;
	
	//oeste
    SPRITEbarco[ 4 ].x = 50;
    SPRITEbarco[ 4 ].y = 0;
    SPRITEbarco[ 4 ].w = 50;
    SPRITEbarco[ 4 ].h = 50;

    //sudoeste
    SPRITEbarco[ 5 ].x = 50;
    SPRITEbarco[ 5 ].y = 100;
    SPRITEbarco[ 5 ].w = 50;
    SPRITEbarco[ 5 ].h = 50;

    //sul
    SPRITEbarco[ 6 ].x = 50;
    SPRITEbarco[ 6 ].y = 50;
    SPRITEbarco[ 6 ].w = 50;
    SPRITEbarco[ 6 ].h = 50;

    //sudeste
    SPRITEbarco[ 7 ].x = 50;
    SPRITEbarco[ 7 ].y = 150;
    SPRITEbarco[ 7 ].w = 50;
    SPRITEbarco[ 7 ].h = 50;
	
	return titanic;
}

void BARCOverifica_movimento(barco titanic, SDL_Event event) {
    /* Se uma tecla foi pressionada */
    if( event.type == SDL_KEYDOWN )
    {
        /* Verifica se há movimento ou rotação do barco */
        switch( event.key.keysym.sym )
        {
			case SDLK_UP: titanic->anda = 1; break;
            case SDLK_DOWN: titanic->anda = -1; break;
			case SDLK_LEFT: titanic->rotacao = 1; break;
            case SDLK_RIGHT: titanic->rotacao = -1; break;
        }
		contador = 4;
    }
    /* Se uma tecla foi liberada */
    else if( event.type == SDL_KEYUP )
    {
        /* Verifica se há movimento ou rotação do barco */
        switch( event.key.keysym.sym )
        {
			case SDLK_UP: titanic->anda = 0; break;
            case SDLK_DOWN: titanic->anda = 0; break;
			case SDLK_LEFT: titanic->rotacao = 0; break;
            case SDLK_RIGHT: titanic->rotacao = 0; break;
        }
    }
}

void BARCOmove(barco titanic, terreno *tijolo) {
	
	/*  Verficamos se o barco está se movendo ou não */
	if(titanic -> anda != 0){ /*  Aqui o barco se move, para frente ou para trás, então nós adicionamos sua velocidade */
		switch( titanic -> direcao )
		{
			case 0: titanic->xVel += (titanic -> anda)*LARGURA_BARCO / 5; if(titanic->yVel > 0)titanic->yVel--; if(titanic->yVel < 0)titanic->yVel++; break;
			case 1: titanic->xVel += (titanic -> anda)*LARGURA_BARCO / 10; titanic->yVel -= (titanic -> anda)*ALTURA_BARCO / 10; break;
			case 2: titanic->yVel -= (titanic -> anda)*ALTURA_BARCO / 5; if(titanic->xVel > 0)titanic->xVel--; if(titanic->xVel < 0)titanic->xVel++; break;
			case 3: titanic->yVel -= (titanic -> anda)*ALTURA_BARCO / 10; titanic->xVel -= (titanic -> anda)*LARGURA_BARCO / 10; break;
			case 4: titanic->xVel -= (titanic -> anda)*LARGURA_BARCO / 5; if(titanic->yVel > 0)titanic->yVel--; if(titanic->yVel < 0)titanic->yVel++; break;
			case 5: titanic->xVel -= (titanic -> anda)*LARGURA_BARCO / 10; titanic->yVel += (titanic -> anda)*LARGURA_BARCO / 10; break;
			case 6: titanic->yVel += (titanic -> anda)*LARGURA_BARCO / 5; if(titanic->xVel > 0)titanic->xVel--; if(titanic->xVel < 0)titanic->xVel++; break;
			case 7: titanic->xVel += (titanic -> anda)*LARGURA_BARCO / 10; titanic->yVel += (titanic -> anda)*LARGURA_BARCO / 10; break;
		}
	}
	else if(titanic -> anda == 0){ /*  Quando paramos de mover o barco temos que realizar o atrito para deixar sua velocidade nula */
		if(titanic->xVel > 0) titanic->xVel -= 1;
		if(titanic->yVel > 0) titanic->yVel -= 1;
		if(titanic->xVel < 0) titanic->xVel += 1;
		if(titanic->yVel < 0) titanic->yVel += 1;
	}
	/*  Não deixamos o barco ultrapassar uma velocidade máxima */
	if(titanic->xVel > VEL_MAX) titanic->xVel = VEL_MAX;
	if(titanic->xVel < -VEL_MAX) titanic->xVel = -VEL_MAX;
	if(titanic->yVel > VEL_MAX) titanic->yVel = VEL_MAX;
	if(titanic->yVel < -VEL_MAX) titanic->yVel = -VEL_MAX;
	
    /*  Passamos a nova posição x para o barco */
	titanic->box.x += titanic->xVel;

    /* Checamos se o barco passou dos limites da tela */
    if( ( titanic->box.x+8 < 0 ) || ( titanic->box.x + LARGURA_BARCO-8 > LARGURA_TELA ) || BARCOtoca_terreno(titanic, tijolo))
    {
        //move back
        titanic->box.x -= titanic->xVel;
    }
	/*  Passamos a nova posição y para o barco */
	titanic->box.y += titanic->yVel;
	
    /* Checamos se o barco passou dos limites da tela */
    if( ( titanic->box.y+8 < 0 ) || ( titanic->box.y + ALTURA_BARCO-8 > ALTURA_TELA ) || BARCOtoca_terreno(titanic, tijolo))
    {
        //move back
        titanic->box.y -= titanic->yVel;
    }
	
	/* Realizamos um delay para a rotação do barco */
	contador++;
	if(contador == 5){
		titanic->direcao += titanic->rotacao;
		if(titanic->direcao == -1) titanic->direcao = 7;
		titanic->direcao = titanic->direcao % 8;
		contador = 0;	
	}
	
}

void BARCOshow(barco titanic, SDL_Surface* SUPERFICIEbarco, SDL_Surface* tela) {
    /* Mostra o barco */
    aplica_superficie( titanic->box.x, titanic->box.y, SUPERFICIEbarco, tela, &SPRITEbarco[ titanic->direcao ] );
}

boolean BARCOverifica_colisao(SDL_Rect A, SDL_Rect B)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    /*leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;*/
	
	leftA = A.x + 12;
	rightA = A.x + A.w - 12;
	topA = A.y + 12;
	bottomA = A.y + A.h - 12;
	
    //Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )return false;
    if( topA >= bottomB )return false;
    if( rightA <= leftB )return false;
    if( leftA >= rightB )return false;

    //If none of the sides from A are outside B
    return true;
}

boolean BARCOtoca_terreno( barco titanic, terreno *tijolo )
{
	int t;
   
	//Go through the tijolo
    for(t = 0; t < 192; t++ )
    {
        //If the tile is a wall type tile
        if( tijolo[t]->tipo < 14 )
        {
            //If the collision box touches the wall tile
            if( BARCOverifica_colisao(titanic->box, tijolo[ t ] -> box )) return true;    
        }
    }
  
    //If no wall tijolo were touched
    return false;
}
