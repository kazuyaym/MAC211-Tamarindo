#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include <string.h>

#include "superficie.h"
#include "inimigo.h"
#include "mapa.h"
#include "barco.h"
#include "timer.h"
#include "botao.h"

/* Atribuicoes da superficie */
#define LARGURA_TELA 800
#define ALTURA_TELA 600
#define BPP_TELA 32
#define FRAMES_POR_SEGUNDO 20

#define boolean int
#define true 1
#define false 0

/* Superfícies */
SDL_Surface *SUPERFICIEtela = NULL;
SDL_Surface *SUPERFICIEmsgmorte = NULL;
SDL_Surface *SUPERFICIEbackground = NULL;
SDL_Surface *SUPERFICIEonda = NULL;
SDL_Surface *SUPERFICIEperola = NULL;
SDL_Surface *SUPERFICIEmonstro[15];
SDL_Surface *SUPERFICIEazulejo = NULL;
SDL_Surface *SUPERFICIEbotaoInicio = NULL;
SDL_Surface *SUPERFICIEbotaoInstrucoes = NULL;
SDL_Surface *SUPERFICIEbotaoSair = NULL;
SDL_Surface *SUPERFICIEbotaoPular = NULL;
SDL_Surface *SUPERFICIEbotaoVoltar = NULL;

/* Portal para passar de tela */
SDL_Rect portal;


/* Sons */
Mix_Music *MUSICAambiente = NULL;

Mix_Chunk *SOMexplosao = NULL;
Mix_Chunk *SOMgrito = NULL;
Mix_Chunk *SOMmordida = NULL;
Mix_Chunk *SOMbolha = NULL;
Mix_Chunk *SOMmotor = NULL;

/* Variável, numero de monstros em jogo */
int n = 0;

/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/

boolean inicializar() {
    /* Inicializa todos os subsistemas dao SDL */
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) return false;

    /* Prepara a tela */
    SUPERFICIEtela = SDL_SetVideoMode( LARGURA_TELA, ALTURA_TELA, BPP_TELA, SDL_SWSURFACE );

    /* Se ocorreu algum erro */
    if( SUPERFICIEtela == NULL ) return false;
    
    /* Abre o som e verifica se está tudo bem */
    if( Mix_OpenAudio( 22050, AUDIO_S16SYS, 2, 4096 ) == -1 ) return false;

    /* Prepara a leganda da tela */
    SDL_WM_SetCaption( "Tamarindo", NULL );

    /* Se tudo foi inicializado corretamente */
    return true;
}

/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/

boolean carrega_fase(int fase, barco perola, inimigo *monstro, int op) {
	
	if(!op) perola->vida = 3;
	/* Carrega arquivos na superfície e verifica se tudo ocorreu bem */
	switch (fase){
		case 1:
			/* Terreno */
			SUPERFICIEazulejo = carrega_imagem( "imagens/mato.png" );
			if( SUPERFICIEazulejo == NULL ) return false;
		
			/* Oceano */
			SUPERFICIEonda = carrega_imagem( "imagens/background1-1.png" );
			if( SUPERFICIEonda == NULL ) return false;
			
			portal.x = 770;
			portal.y = 100;
			portal.w = 25;
			portal.h = 275;
			
			perola->box.x = 100;
			perola->box.y = 520;
			perola->direcao = 2;
			
			n = 0;
			
			if(!op) monstro[n] = INIMIGOinicializa(2);
			monstro[n] -> xVel = 0; monstro[n] -> yVel = -1;			
			monstro[n] -> x0 = monstro[n] -> box.x = 240;
			monstro[n] -> y0 = monstro[n] -> box.y = 425;
			monstro[n] -> yInf = 150;
			n++;
			
			if(!op) monstro[n] = INIMIGOinicializa(2);
			monstro[n] -> xVel = 0;	monstro[n] -> yVel = 1;			
			monstro[n] -> x0 = monstro[n] -> box.x = 375;
			monstro[n] -> y0 = monstro[n] -> box.y = 125;
			monstro[n] -> ySup = 450;
			n++;
			
			if(!op) monstro[n] = INIMIGOinicializa(2);
			monstro[n] -> xVel = 0;	monstro[n] -> yVel = 1;			
			monstro[n] -> x0 = monstro[n] -> box.x = 520;
			monstro[n] -> y0 = 125; monstro[n] -> box.y = 300;
			monstro[n] -> ySup = 430;
			n++;
			
			if(!op) monstro[n] = INIMIGOinicializa(2);
			monstro[n] -> xVel = 0;	monstro[n] -> yVel = -1;			
			monstro[n] -> x0 = monstro[n] -> box.x = 580;
			monstro[n] -> y0 = monstro[n] -> box.y = 364;
			monstro[n] -> yInf = 110;
			n++;
			
			if(!op) monstro[n] = INIMIGOinicializa(2);
			monstro[n] -> xVel = 0;	monstro[n] -> yVel = -1;			
			monstro[n] -> x0 = monstro[n] -> box.x = 700;
			monstro[n] -> y0 = 364; monstro[n] -> box.y = 200;
			monstro[n] -> yInf = 50;
			n++;
			
			if(!op) monstro[n] = INIMIGOinicializa(4);
			monstro[n] -> box.x = 660; monstro[n] -> box.y = 340;
			n++;
			
			if(!op) monstro[n] = INIMIGOinicializa(5);
			monstro[n] -> box.x = 560; monstro[n] -> box.y = 325;
			n++;
			
			if(!op) monstro[n] = INIMIGOinicializa(6);
			monstro[n] -> box.x = 220; monstro[n] -> box.y = 390;
			n++;
			
			if(!op) monstro[n] = INIMIGOinicializa(7);
			monstro[n] -> box.x = 360; monstro[n] -> box.y = 0;
			n++;
			
		break;
		case 2:
			/* Terreno */
			SUPERFICIEazulejo = carrega_imagem( "imagens/mato2.png" );
			if( SUPERFICIEazulejo == NULL ) return false;
	
			/* Oceano */
			SUPERFICIEonda = carrega_imagem( "imagens/background2.png" );
			if( SUPERFICIEonda == NULL ) return false;
		
			portal.x = 225;
			portal.y = 575;
			portal.w = 225;
			portal.h = 25;
			
			perola->box.x = 10;
			perola->box.y = 300;
			perola->direcao = 0;
			
			n = 0;
			
			if(!op) monstro[n] = INIMIGOinicializa(3);
			monstro[n] -> box.x = 100;
			monstro[n] -> box.y = 150;
			n++;
			
			if(!op) monstro[n] = INIMIGOinicializa(1);
			monstro[n] -> xVel = 7; monstro[n] -> yVel = 7;			
			monstro[n] -> xInf = 125;
			monstro[n] -> yInf = 115;
			monstro[n] -> ySup = 220;
			monstro[n] -> box.x = 145;
			monstro[n] -> box.y = 135;
			monstro[n] -> x0 = -1;
			monstro[n] -> y0 = -1;
			n++;
			
			if(!op) monstro[n] = INIMIGOinicializa(1);
			monstro[n] -> xVel = 6; monstro[n] -> yVel = 0;			
			monstro[n] -> xInf = 300;
			monstro[n] -> yInf = 115;
			monstro[n] -> xSup = 575;
			monstro[n] -> ySup = 600;
			monstro[n] -> box.x = 350;
			monstro[n] -> box.y = 115;
			monstro[n] -> x0 = -1;
			monstro[n] -> y0 = 0;
			n++;
			
			if(!op) monstro[n] = INIMIGOinicializa(1);
			monstro[n] -> xVel = 4; monstro[n] -> yVel = 0;			
			monstro[n] -> xInf = 200;
			monstro[n] -> xSup = 575;
			monstro[n] -> ySup = 600;
			monstro[n] -> box.x = 500;
			monstro[n] -> box.y = 200;
			monstro[n] -> x0 = -1;
			monstro[n] -> y0 = 0;
			n++;
			
			if(!op) monstro[n] = INIMIGOinicializa(1);
			monstro[n] -> xVel = 7; monstro[n] -> yVel = 7;			
			monstro[n] -> xInf = 450;
			monstro[n] -> yInf = 150;
			monstro[n] -> xSup = 600;
			monstro[n] -> ySup = 250;
			monstro[n] -> box.x = 600;
			monstro[n] -> box.y = 150;
			monstro[n] -> x0 = -1;
			monstro[n] -> y0 = 1;
			n++;
			
			if(!op) monstro[n] = INIMIGOinicializa(1);
			monstro[n] -> xVel = 6; monstro[n] -> yVel = 0;			
			monstro[n] -> xInf = 450;
			monstro[n] -> xSup = 700;
			monstro[n] -> box.x = 500;
			monstro[n] -> box.y = 280;
			monstro[n] -> x0 = -1;
			monstro[n] -> y0 = 0;
			n++;
			
			if(!op) monstro[n] = INIMIGOinicializa(3);
			monstro[n] -> box.x = 470;
			monstro[n] -> box.y = 350;
			n++;
			
			if(!op) monstro[n] = INIMIGOinicializa(3);
			monstro[n] -> box.x = 660;
			monstro[n] -> box.y = 300;
			n++;
			
			if(!op) monstro[n] = INIMIGOinicializa(1);
			monstro[n] -> xVel = 7; monstro[n] -> yVel = 7;			
			monstro[n] -> xInf = 350;
			monstro[n] -> yInf = 450;
			monstro[n] -> xSup = 425;
			monstro[n] -> ySup = 525;
			monstro[n] -> box.x = 425;
			monstro[n] -> box.y = 525;
			monstro[n] -> x0 = -1;
			monstro[n] -> y0 = -1;
			n++;
			
		break;
		case 3:
			/* Terreno */
			SUPERFICIEazulejo = carrega_imagem( "imagens/mato3.png" );
			if( SUPERFICIEazulejo == NULL ) return false;
	
			/* Oceano */
			SUPERFICIEonda = carrega_imagem( "imagens/background3.png" );
			if( SUPERFICIEonda == NULL ) return false;
			
			portal.x = 770;
			portal.y = 350;
			portal.w = 25;
			portal.h = 400;
			
			perola->box.x = 700;
			perola->box.y = 5;
			perola->direcao = 6;
			
			n = 0;
			
			if(!op) monstro[n] = INIMIGOinicializa(0);
			/* Centro do circulo  */
			monstro[n] -> x0 = 470;
			monstro[n] -> y0 = 170;
			
			monstro[n] -> xInf = 9; /* velocidade */
			monstro[n] -> xSup = 120; /* raio */
			
			monstro[n] -> yInf = -1; /* quadrante inicial e lado que irá girar */
			monstro[n] -> ySup = 1; 
			n++;
			
			if(!op) monstro[n] = INIMIGOinicializa(0);
			/* Centro do circulo  */
			monstro[n] -> x0 = 470;
			monstro[n] -> y0 = 170;
			
			monstro[n] -> xInf = 9; /* velocidade */
			monstro[n] -> xSup = 120; /* raio */
			
			monstro[n] -> yInf = 1; /* quadrante inicial e lado que irá girar */
			monstro[n] -> ySup = -1; 
			n++;
			
			if(!op) monstro[n] = INIMIGOinicializa(0);
			/* Centro do circulo  */
			monstro[n] -> x0 = 470;
			monstro[n] -> y0 = 170;
			
			monstro[n] -> xInf = 6; /* velocidade */
			monstro[n] -> xSup = 70; /* raio */
			
			monstro[n] -> yInf = 1; /* quadrante inicial e lado que irá girar */
			monstro[n] -> ySup = 1; 
			n++;
			
			if(!op) monstro[n] = INIMIGOinicializa(0);
			/* Centro do circulo  */
			monstro[n] -> x0 = 470;
			monstro[n] -> y0 = 170;
			
			monstro[n] -> xInf = 5; /* velocidade */
			monstro[n] -> xSup = 30; /* raio */
			
			monstro[n] -> yInf = 1; /* quadrante inicial e lado que irá girar */
			monstro[n] -> ySup = -1; 
			n++;
			
			if(!op) monstro[n] = INIMIGOinicializa(8);
			monstro[n] -> box.x = 100;
			monstro[n] -> box.y = 110;
			n++;
			
			if(!op) monstro[n] = INIMIGOinicializa(0);
			/* Centro do circulo  */
			monstro[n] -> x0 = 130;
			monstro[n] -> y0 = 140;
			
			monstro[n] -> xInf = 6; /* velocidade */
			monstro[n] -> xSup = 100; /* raio */
			
			monstro[n] -> yInf = -1; /* quadrante inicial e lado que irá girar */
			monstro[n] -> ySup = -1; 
			n++;
			
			if(!op) monstro[n] = INIMIGOinicializa(0);
			/* Centro do circulo  */
			monstro[n] -> x0 = 130;
			monstro[n] -> y0 = 140;
			
			monstro[n] -> xInf = 6; /* velocidade */
			monstro[n] -> xSup = 100; /* raio */
			
			monstro[n] -> yInf = 1; /* quadrante inicial e lado que irá girar */
			monstro[n] -> ySup = 1; 
			n++;
			
			if(!op) monstro[n] = INIMIGOinicializa(8);
			monstro[n] -> box.x = 120;
			monstro[n] -> box.y = 400;
			n++;
			
			if(!op) monstro[n] = INIMIGOinicializa(0);
			/* Centro do circulo  */
			monstro[n] -> x0 = 150;
			monstro[n] -> y0 = 440;
			
			monstro[n] -> xInf = 7; /* velocidade */
			monstro[n] -> xSup = 110; /* raio */
			
			monstro[n] -> yInf = -1; /* quadrante inicial e lado que irá girar */
			monstro[n] -> ySup = +1; 
			n++;
			
			if(!op) monstro[n] = INIMIGOinicializa(0);
			/* Centro do circulo  */
			monstro[n] -> x0 = 150;
			monstro[n] -> y0 = 440;
			
			monstro[n] -> xInf = 7; /* velocidade */
			monstro[n] -> xSup = 110; /* raio */
			
			monstro[n] -> yInf = +1; /* quadrante inicial e lado que irá girar */
			monstro[n] -> ySup = -1; 
			n++;
			
			if(!op) monstro[n] = INIMIGOinicializa(8);
			monstro[n] -> box.x = 465;
			monstro[n] -> box.y = 400;
			n++;
			
			if(!op) monstro[n] = INIMIGOinicializa(0);
			/* Centro do circulo  */
			monstro[n] -> x0 = 500;
			monstro[n] -> y0 = 400;
			
			monstro[n] -> xInf = 8; /* velocidade */
			monstro[n] -> xSup = 100; /* raio */
			
			monstro[n] -> yInf = -1; /* quadrante inicial e lado que irá girar */
			monstro[n] -> ySup = +1; 
			n++;
			
			if(!op) monstro[n] = INIMIGOinicializa(0);
			/* Centro do circulo  */
			monstro[n] -> x0 = 500;
			monstro[n] -> y0 = 400;
			
			monstro[n] -> xInf = 8; /* velocidade */
			monstro[n] -> xSup = 100; /* raio */
			
			monstro[n] -> yInf = +1; /* quadrante inicial e lado que irá girar */
			monstro[n] -> ySup = -1; 
			n++;
			
		break;
		case 4:
			/* Terreno */
			SUPERFICIEazulejo = carrega_imagem( "imagens/mato.png" );
			if( SUPERFICIEazulejo == NULL ) return false;
		
			/* Oceano */
			SUPERFICIEonda = carrega_imagem( "imagens/background1-1.png" );
			if( SUPERFICIEonda == NULL ) return false;
		
			portal.x = 770;
			portal.y = 570;
			portal.w = 25;
			portal.h = 25;
			
			perola->box.x = 100;
			perola->box.y = 550;
			perola->direcao = 1;
		
			n = 0;
			
			if(!op) monstro[n] = INIMIGOinicializa(9);
			monstro[n] -> box.x = 0;
			monstro[n] -> box.y = 300;
			n++;
			
			if(!op) monstro[n] = INIMIGOinicializa(10);
			monstro[n] -> box.x = 325;
			monstro[n] -> box.y = 180;
			n++;
			
			if(!op) monstro[n] = INIMIGOinicializa(1);
			monstro[n] -> xVel = 2; monstro[n] -> yVel = 0;			
			monstro[n] -> xInf = 225;
			monstro[n] -> xSup = 600;
			monstro[n] -> yInf = 60;
			monstro[n] -> ySup = 60;
			monstro[n] -> box.x = 500;
			monstro[n] -> box.y = 60;
			monstro[n] -> x0 = -1;
			monstro[n] -> y0 = 0;
			n++;
			
			if(!op) monstro[n] = INIMIGOinicializa(1);
			monstro[n] -> xVel = 2; monstro[n] -> yVel = 0;			
			monstro[n] -> xInf = 225;
			monstro[n] -> xSup = 600;
			monstro[n] -> yInf = 65;
			monstro[n] -> ySup = 65;
			monstro[n] -> box.x = 497;
			monstro[n] -> box.y = 65;
			monstro[n] -> x0 = -1;
			monstro[n] -> y0 = 0;
			n++;
			
			if(!op) monstro[n] = INIMIGOinicializa(1);
			monstro[n] -> xVel = 4; monstro[n] -> yVel = 0;			
			monstro[n] -> xInf = 175;
			monstro[n] -> xSup = 353;
			monstro[n] -> yInf = 120;
			monstro[n] -> ySup = 120;
			monstro[n] -> box.x = 203;
			monstro[n] -> box.y = 120;
			monstro[n] -> x0 = -1;
			monstro[n] -> y0 = 0;
			n++;
			
			if(!op) monstro[n] = INIMIGOinicializa(11);
			monstro[n] -> box.x = 515;
			monstro[n] -> box.y = 155;
			n++;
			
			if(!op) monstro[n] = INIMIGOinicializa(12);
			monstro[n] -> box.x = 620;
			monstro[n] -> box.y = 300;
			n++;
			
			if(!op) monstro[n] = INIMIGOinicializa(2);
			monstro[n] -> xVel = 2; monstro[n] -> yVel = 0;			
			monstro[n] -> x0 = monstro[n] -> box.x = 560;
			monstro[n] -> y0 = monstro[n] -> box.y = 135;
			monstro[n] -> xSup = 1000;
			n++;
			
			if(!op) monstro[n] = INIMIGOinicializa(0);
			/* Centro do circulo  */
			monstro[n] -> x0 = 700;
			monstro[n] -> y0 = 400;
			
			monstro[n] -> xInf = 8; /* velocidade */
			monstro[n] -> xSup = 200; /* raio */
			
			monstro[n] -> yInf = -1; /* quadrante inicial e lado que irá girar */
			monstro[n] -> ySup = +1; 
			n++;
			
			if(!op) monstro[n] = INIMIGOinicializa(0);
			/* Centro do circulo  */
			monstro[n] -> x0 = 700;
			monstro[n] -> y0 = 400;
			
			monstro[n] -> xInf = 8; /* velocidade */
			monstro[n] -> xSup = 200; /* raio */
			
			monstro[n] -> yInf = +1; /* quadrante inicial e lado que irá girar */
			monstro[n] -> ySup = -1; 
			n++;
			
			
			if(!op) monstro[n] = INIMIGOinicializa(13);
			monstro[n] -> box.x = monstro[n] -> x0 = 145;
			monstro[n] -> box.y = monstro[n] -> y0 = 330;
			monstro[n] -> ySup = 15; 
			n++;
			
			if(!op) monstro[n] = INIMIGOinicializa(14);
			monstro[n] -> box.x = monstro[n] -> x0 = 90;
			monstro[n] -> box.y = monstro[n] -> y0 = 200;
			monstro[n] -> ySup = -5; 
			n++;
			
		break;
	}
	
	/*EXEMPLOS DE MONSTROS*/
	/*if(!op) monstro[0] = INIMIGOinicializa(0); fantasma
			monstro[0] -> x0 = 350;
			monstro[0] -> y0 = 250; 
			monstro[0] -> xVel = 0;
			monstro[0] -> yVel = 0;
			
			
			if(!op) monstro[2] = INIMIGOinicializa(1); tubarao
			monstro[2] -> x0 = 1;	
			monstro[2] -> box.x = 100;
			monstro[2] -> box.y = 300;			
			
			if(!op) monstro[3] = INIMIGOinicializa(2); bomba
			monstro[3] -> xVel = 1;
			monstro[3] -> yVel = 0;			
			monstro[3] -> x0 = monstro[3] -> box.x = 100;
			monstro[3] -> y0 = monstro[3] -> box.y = 200;
			
			if(!op) monstro[4] = INIMIGOinicializa(3);	 polvo	
			monstro[4] -> box.x = 250;
			monstro[4] -> box.y = 400;*/
	/* Se tudo ocorreu bem */
	return true;
}

/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/

boolean carrega_arquivos(){
/* Carrega as imagens de cada elemento e verifica se ocorreu tudo bem */
	int i;
	for(i = 0; i < 14; i++)	SUPERFICIEmonstro[i] = NULL;

	/* Barco */
	SUPERFICIEperola = carrega_imagem( "imagens/sboat.png" );
	if( SUPERFICIEperola == NULL ) return false;
	
	/* Monstro */
	SUPERFICIEmonstro[0] = carrega_imagem( "imagens/monstro0.png" );	
	SUPERFICIEmonstro[1] = carrega_imagem( "imagens/monstro1-d.png" );	
	SUPERFICIEmonstro[2] = carrega_imagem( "imagens/monstro2.png" );	
	SUPERFICIEmonstro[3] = carrega_imagem( "imagens/monstro3.png" );	
	SUPERFICIEmonstro[4] = carrega_imagem( "imagens/monstro4.png" );
	SUPERFICIEmonstro[5] = carrega_imagem( "imagens/monstro5.png" );	
	SUPERFICIEmonstro[6] = carrega_imagem( "imagens/monstro6.png" );	
	SUPERFICIEmonstro[7] = carrega_imagem( "imagens/monstro7.png" );	
	SUPERFICIEmonstro[8] = carrega_imagem( "imagens/monstro8.png" );	
	SUPERFICIEmonstro[9] = carrega_imagem( "imagens/monstro9.png" );	
	SUPERFICIEmonstro[10] = carrega_imagem( "imagens/monstro10.png" );
	SUPERFICIEmonstro[11] = carrega_imagem( "imagens/monstro11.png" );	
	SUPERFICIEmonstro[12] = carrega_imagem( "imagens/monstro12.png" );
	SUPERFICIEmonstro[13] = carrega_imagem( "imagens/monstro13-1.png" );
	SUPERFICIEmonstro[14] = carrega_imagem( "imagens/monstro14-1.png" );
	for(i = 0; i < 15; i++) if( SUPERFICIEmonstro[i] == NULL ) return false;
	
	/* Background */
	SUPERFICIEbackground = carrega_imagem( "imagens/background1.png" );
	if( SUPERFICIEbackground == NULL ) return false;
	
	/* Mensagem */
	SUPERFICIEmsgmorte = carrega_imagem( "imagens/morte.png" );
	if( SUPERFICIEmsgmorte == NULL ) return false;
	
	/* Botões */
	SUPERFICIEbotaoInicio = carrega_imagem( "imagens/Iniciar.png" );
	if( SUPERFICIEbotaoInicio == NULL ) return false;
	
	SUPERFICIEbotaoInstrucoes = carrega_imagem( "imagens/Instrucao.png" );
	if( SUPERFICIEbotaoInstrucoes == NULL ) return false;
	
	SUPERFICIEbotaoSair = carrega_imagem( "imagens/Sair.png" );
	if( SUPERFICIEbotaoSair == NULL ) return false;
	
	SUPERFICIEbotaoVoltar = carrega_imagem( "imagens/Voltar.png" );
	if( SUPERFICIEbotaoVoltar == NULL ) return false;
	
	SUPERFICIEbotaoPular = carrega_imagem( "imagens/Pular.png" );
	if( SUPERFICIEbotaoPular == NULL ) return false;
	
	/* Carrega os sons que serão usados no jogo */
	MUSICAambiente = Mix_LoadMUS( "sons/bach.mp3" );
    SOMgrito = Mix_LoadWAV( "sons/2scream.wav" );
    SOMexplosao = Mix_LoadWAV( "sons/Fireball3.wav" );
    SOMbolha = Mix_LoadWAV( "sons/bubble.wav" );
    SOMmordida = Mix_LoadWAV( "sons/bite1.wav" );
    SOMmotor = Mix_LoadWAV( "sons/motor_1.wav" );
	
	return true;
}

/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/

void limpa_tudo() { /* Libera as superficies */
	int i;

	SDL_FreeSurface( SUPERFICIEbackground ); /* Background */
	SDL_FreeSurface( SUPERFICIEonda ); /* Onda */
	SDL_FreeSurface( SUPERFICIEperola ); /* Barco */
	SDL_FreeSurface( SUPERFICIEazulejo ); /* Terreno */
	SDL_FreeSurface( SUPERFICIEmsgmorte ); /* Mensagem */
	SDL_FreeSurface( SUPERFICIEbotaoInicio ); /* Botao */
	SDL_FreeSurface( SUPERFICIEbotaoInstrucoes ); /* Botao */
	SDL_FreeSurface( SUPERFICIEbotaoSair ); /* Botao */
	SDL_FreeSurface( SUPERFICIEbotaoVoltar ); /* Botao */
	SDL_FreeSurface( SUPERFICIEbotaoPular ); /* Botao */
	for(i = 0; i <= 14; i++) SDL_FreeSurface( SUPERFICIEmonstro[i] ); /* Monstros */
	
	/* Libera os sons */
    Mix_FreeMusic( MUSICAambiente );
    Mix_FreeChunk( SOMmordida );
    Mix_FreeChunk( SOMgrito );
    Mix_FreeChunk( SOMbolha );
    Mix_FreeChunk( SOMexplosao );
    Mix_FreeChunk( SOMmotor );
	
    /* Sai do SDL */
	Mix_CloseAudio();
    SDL_Quit();

}

/******************************************************************************************************************/
/***********************************************             ******************************************************/
/***********************************************     MAIN    ******************************************************/
/***********************************************             ******************************************************/
/******************************************************************************************************************/

int main( int argc, char* argv[] ) {
	
	
	SDL_Event evento1, evento2; /* Evento */
	boolean quit = false; /* Flag de saida */
	barco perola; /* Barco */
	inimigo monstro[50]; /* Inimigos */
	terreno *azulejo; /*  Terrenos */
	Timer fps; /* Frames por segundo */
	botao botaoInicio, botaoInstrucoes, botaoSair, botaoVoltar, botaoPular; /* Botões */
	
	/* Variáveis */
	int fase = 1, i = 0;
	int x = 0, y = 0;
	int cFundo = 0;
	int mudaFogo = 0;
	/* ------------------------------------------------------------------------------- */
	/* ------------------------------------------------------------------------------- */
	/* --------------------------          Inicializa            --------------------- */
	/* ------------------------------------------------------------------------------- */
	/* ------------------------------------------------------------------------------- */
	
    if( inicializar() == false ) return 1;
	
	perola = BARCOinicializa(); 
	fps = TIMERinicializa();
	botaoInicio = BOTAOinicializa();
	botaoInstrucoes = BOTAOinicializa();
	botaoSair = BOTAOinicializa();
	botaoVoltar = BOTAOinicializa();
	botaoPular = BOTAOinicializa();
	
	
	if( carrega_arquivos() == false ) return 1; /* Carrega as imagens do jogo */

    if( Mix_PlayMusic( MUSICAambiente, -1 ) == -1 ) return 1; /* Toca a música de fundo */
	
	TERRENOsepara_sprites(); /* Corta as imagens do sprite do terreno */
	BOTAOsepara_sprites(); /* Corta as imagens do sprite do botaoInicio */
	
	botaoInicio->box.x = 500; botaoInicio->box.y = 300;
	botaoInstrucoes->box.x = 500; botaoInstrucoes->box.y = 450;
	botaoSair->box.x = 500; botaoSair->box.y = 500;
	botaoPular->box.x = 500; botaoPular->box.y = 570;
	botaoVoltar->box.x = 500; botaoVoltar->box.y = 500;

	/* ------------------------------------------------------------------------------- */
	/* ------------------------------------------------------------------------------- */
	/* --------------                  Looping do jogo                   ------------- */
	/* ------------------------------------------------------------------------------- */
	/* ------------------------------------------------------------------------------- */
	
	while( quit == false ) {
	
		/* --- --- --- --- --- --- --- --- --- --- --- --- --- --- - */
		/* --- --- --- --- --- --- Tela inicial --- --- ---  --- --- */
		/* --- --- --- --- --- --- --- --- --- --- --- --- --- --- - */
		
		/* Oceano */
		SUPERFICIEonda = carrega_imagem( "imagens/inicio.jpg" );
		if( SUPERFICIEonda == NULL ) return false;
		
		aplica_superficie( 0, 0, SUPERFICIEonda, SUPERFICIEtela, NULL );
		
		/* Aplica os botões */
		BOTAOshow( botaoInicio, SUPERFICIEbotaoInicio, SUPERFICIEtela);
		BOTAOshow( botaoInstrucoes, SUPERFICIEbotaoInstrucoes, SUPERFICIEtela);
		BOTAOshow( botaoSair, SUPERFICIEbotaoSair, SUPERFICIEtela);
		
		if( SDL_Flip( SUPERFICIEtela ) == -1 ) return 1;
		
		/* --- --- --- --- --- Verifica se algum botão foi pressionado --- --- --- --- --- */
		
		while( SDL_PollEvent( &evento1 ) ) {
		
			BOTAOgerencia_evento(botaoInicio, evento1);
			BOTAOgerencia_evento(botaoInstrucoes, evento1);
			BOTAOgerencia_evento(botaoSair, evento1);
			
			/* -------------------- Se o botão de inicio de jogo for pressionado --------------------------- */
			if( botaoInicio->ind == 3 ){
				/* -------------- História ------------- */
				
				while( i != 320 ){
					while( SDL_PollEvent( &evento1 ) )
						BOTAOgerencia_evento(botaoPular, evento1);
						
					SUPERFICIEonda = carrega_imagem( "imagens/historia1.jpg" );
					if( SUPERFICIEonda == NULL ) return false;
					aplica_superficie( 0, 0, SUPERFICIEonda, SUPERFICIEtela, NULL );
					BOTAOshow( botaoPular, SUPERFICIEbotaoPular, SUPERFICIEtela);
					if( SDL_Flip( SUPERFICIEtela ) == -1 ) return 1;
					
					i++;
					if(botaoPular->ind == 3)
						i = 320;
				}
				botaoPular->ind = 1;
				i = 0;
				
				while( i != 320 ){
					while( SDL_PollEvent( &evento1 ) )
						BOTAOgerencia_evento(botaoPular, evento1);
						
					SUPERFICIEonda = carrega_imagem( "imagens/historia2.jpg" );
					if( SUPERFICIEonda == NULL ) return false;
					aplica_superficie( 0, 0, SUPERFICIEonda, SUPERFICIEtela, NULL );
					BOTAOshow( botaoPular, SUPERFICIEbotaoPular, SUPERFICIEtela);
					if( SDL_Flip( SUPERFICIEtela ) == -1 ) return 1;
					
					i++;
					if(botaoPular->ind == 3)
						i = 320;
				}
				i = 0;
				botaoPular->ind = 1;
				
				while( i != 320 ){
					while( SDL_PollEvent( &evento1 ) )
						BOTAOgerencia_evento(botaoPular, evento1);
						
					SUPERFICIEonda = carrega_imagem( "imagens/historia3.jpg" );
					if( SUPERFICIEonda == NULL ) return false;
					aplica_superficie( 0, 0, SUPERFICIEonda, SUPERFICIEtela, NULL );
					BOTAOshow( botaoPular, SUPERFICIEbotaoPular, SUPERFICIEtela);
					if( SDL_Flip( SUPERFICIEtela ) == -1 ) return 1;
					
					i++;
					if(botaoPular->ind == 3)
						i = 320;
				}
				i = 0;
				botaoPular->ind = 1;
				
				
				/* ----------------- Carrega fase 1 ------------ */
				azulejo = TERRENOcria_mapa(fase); /* Carrega os fundos do jogo */
				if( carrega_fase(fase++, perola, monstro, 0) == false ) return 1;
				botaoInicio->ind = 1;
				
				
			}
			
			/* -------------------- Se o botão de sair de jogo for pressionado ---------------------------- */
			if( botaoSair->ind == 3 ){
				quit = true;
			}
			
			/* ------------------- Se o botão de instruções de jogo for pressionado ---------------------- */
			if( botaoInstrucoes->ind == 3 ){
				perola->vida = -1;
				while(perola->vida != 0){
					while( SDL_PollEvent( &evento1 ) ){
						BOTAOgerencia_evento(botaoVoltar, evento1);
						
						/* Fundo */
						SUPERFICIEonda = carrega_imagem( "imagens/instrucoes1.jpg" );
						if( SUPERFICIEonda == NULL ) return false;
						
						aplica_superficie( 0, 0, SUPERFICIEonda, SUPERFICIEtela, NULL );
						
						/* Aplica os botões */
						BOTAOshow( botaoVoltar, SUPERFICIEbotaoVoltar, SUPERFICIEtela);
						
						if( SDL_Flip( SUPERFICIEtela ) == -1 ) return 1;
						
						/* Se o botão de inicio de jogo for pressionado */
						if( botaoVoltar->ind == 3 ){
							perola->vida++;
						}
					}
				}
			}
			
			/* Se o usuário fechou a tela */
			if( evento1.type == SDL_QUIT ) {
				/* Feche o programa */
				quit = true;
			}
		}
				
		
		
		/* --- --- --- --- --- --- --- --- --- --- --- --- --- --- - */
		/* --- --- --- --- --- ---Entra no jogo --- --- ---  --- --- */
		/* --- --- --- --- --- --- --- --- --- --- --- --- --- --- - */
				
	
		while ( perola->vida != 0 ){
			TIMERstart(fps); /* Starta o frame timer */
			if( SDL_Flip( SUPERFICIEtela ) == -1 ) return 1; /* Flipa a tela */
			
			/* --- --- --- --- --- --- --- --- --- --- --- --- --- --- - */
			/* --- --- --- Enquanto tiver eventos para lidar --- --- --- */
			/* --- --- --- --- --- --- --- --- --- --- --- --- --- --- - */
			
			while( SDL_PollEvent( &evento2 ) ) {
			
				/* Pausa ou toca musica */
				if( evento2.type == SDL_KEYDOWN ){
					if( evento2.key.keysym.sym == SDLK_m ){ 
						if( Mix_PausedMusic() == 1 ) Mix_ResumeMusic();
						else Mix_PauseMusic();
					}
				}
				BARCOverifica_movimento(perola, evento2);
				
				/* Se o usuário fechou a tela */
				if( evento2.type == SDL_QUIT ) {
					/* Feche o programa */
					quit = true;
					perola->vida = 0;
				}
			}
			
			/* --- --- --- --- --- --- --- --- --- --- --- --- --- */
			/* --- --- --- Move item: barco e inimigos --- --- --- */
			/* --- --- --- --- --- --- --- --- --- --- --- --- --- */
			
			BARCOmove(perola, azulejo); /* barco */
			for(i = 0; i < n; i++) INIMIGOmove(monstro[i]); /*  inimigo */
			switch (cFundo++){ /* fundo */
				case 9: x = 1; y = -1; break;
				case 12: x = 2; y = -2; break; 
				case 15: x = 3; y = -1; break;
				case 18: x = 4; y = 0; break;
				case 27: x = 3; y = 1; break;
				case 30: x = 2; y = 2; break;
				case 33: x = 1; y = 1; break;
				case 36: x = 0; y = 0; cFundo = 0; break;
			}

			/* --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- - */
			/* --- --- --- Verifica colisão com cada monstro na tela --- --- --- */
			/* --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- - */
			
			for(i = 0; i < n; i++){
				if(BARCOverifica_colisao(perola->box, monstro[i]->box)){
					perola -> vida--;
					
					switch (monstro[i]->id){
						case 0: if( Mix_PlayChannel( -1, SOMgrito, 0 ) == -1 ) return 1; break;
						case 1: if( Mix_PlayChannel( -1, SOMmordida, 0 ) == -1 ) return 1; break;
						case 2: if( Mix_PlayChannel( -1, SOMexplosao, 0 ) == -1 ) return 1; break;
						case 3: if( Mix_PlayChannel( -1, SOMbolha, 1 ) == -1 ) return 1; break;
					}
					
					aplica_superficie( 200, 150, SUPERFICIEmsgmorte, SUPERFICIEtela, NULL );
					if( SDL_Flip( SUPERFICIEtela ) == -1 ) return 1;
					SDL_Delay( 2500 );
					
					if(perola -> vida > 0){
						if( carrega_fase(fase-1, perola, monstro, 1) == false ) return 1;
					}
					
					/* game over */
					if(perola -> vida == 0){
					fase = 1;
					
					SUPERFICIEonda = carrega_imagem( "imagens/Fim1.jpg" );
					if( SUPERFICIEonda == NULL ) return false;
					
					aplica_superficie( 0, 0, SUPERFICIEonda, SUPERFICIEtela, NULL );
					if( SDL_Flip( SUPERFICIEtela ) == -1 ) return 1;
					
					SDL_Delay( 4000 );
					
					}
				}
			}
			
			/* --- --- --- --- --- --- --- --- --- --- --- --- -- */
			/* --- --- --- Blita todas as superficies --- --- --- */
			/* --- --- --- --- --- --- --- --- --- --- --- --- -- */
			
			if(fase == 5){
				mudaFogo++;
				if(mudaFogo == 4){
				SUPERFICIEmonstro[13] = carrega_imagem( "imagens/monstro13-1.png" );
				SUPERFICIEmonstro[14] = carrega_imagem( "imagens/monstro14-1.png" );
				mudaFogo = -1;
				}
				if(mudaFogo == 2){
					SUPERFICIEmonstro[13] = carrega_imagem( "imagens/monstro13-2.png" );
					SUPERFICIEmonstro[14] = carrega_imagem( "imagens/monstro14-2.png" );
				}
			}
			aplica_superficie( 0, 0, SUPERFICIEbackground, SUPERFICIEtela, NULL ); /* Aplica o fundo na tela */
			aplica_superficie( x, y, SUPERFICIEonda, SUPERFICIEtela, NULL ); /* Aplica a onda, que se move */
			for(i = 0; i < 192; i++) TERRENOshow(azulejo[i], SUPERFICIEazulejo, SUPERFICIEtela); /* Aplica os terrenos */
			for(i = 0; i < n; i++) INIMIGOshow(monstro[i], SUPERFICIEmonstro[monstro[i]->id], SUPERFICIEtela); /* Aplica os inimigos */
			BARCOshow(perola, SUPERFICIEperola, SUPERFICIEtela); /* Aplica o barco */
			
			/* --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- */
			/* --- --- --- Trata colisão com portal para mudar de fase --- --- --- */
			/* --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- */
		
			if(BARCOverifica_colisao(perola->box, portal)){
				if(fase == 5){
					SUPERFICIEonda = carrega_imagem( "imagens/FinalFeliz.jpg" );
					if( SUPERFICIEonda == NULL ) return false;
					aplica_superficie( 0, 0, SUPERFICIEonda, SUPERFICIEtela, NULL );
					if( SDL_Flip( SUPERFICIEtela ) == -1 ) return 1;
					SDL_Delay( 6000 );
					perola->vida = 0;
				}
				else{
					azulejo = TERRENOcria_mapa(fase);
					if( carrega_fase(fase++, perola, monstro, 0) == false ) return 1;
					SDL_Delay( 1000 );
				}
			}
			
			/* --- --- --- --- --- --- --- --- --- - */
			/* --- --- --- Regula frames --- --- --- */
			/* --- --- --- --- --- --- --- --- --- - */
			
			if( TIMERverifica_ticks(fps) < 1000 / FRAMES_POR_SEGUNDO ){
				SDL_Delay( ( 1000 / FRAMES_POR_SEGUNDO ) - TIMERverifica_ticks(fps) );
			}
		}
	}
	limpa_tudo();
	return 0;
}
