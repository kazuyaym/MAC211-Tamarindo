#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include <string.h>

#include "superficie.h"
#include "mapa.h"

/* Atribuicoes da superficie */
#define LARGURA_TELA 800
#define ALTURA_TELA 600

//TERRENO constants
#define TERRENO_LARGURA 50
#define TERRENO_ALTURA 50
#define TOTAL_TERRENOS 192
#define TERRENO_SPRITES 15

//The different TERRENO sprites
#define TERRENO_LESTE_ISO 0
#define TERRENO_OESTE_ISO 1
#define TERRENO_NORTE_ISO 2
#define TERRENO_NOROESTE 3
#define TERRENO_OESTE 4
#define TERRENO_SUDOESTE 5
#define TERRENO_NORTE 6
#define TERRENO_CENTRO 7
#define TERRENO_SUL 8
#define TERRENO_NORDESTE 9
#define TERRENO_LESTE 10
#define TERRENO_SUDESTE 11
#define TERRENO_SUL_ISO 12
#define TERRENO_CENTRO_ISO 13
#define TERRENO_NULO 14

#define boolean int
#define true 1
#define false 0

SDL_Rect SPRITEterreno[ TERRENO_SPRITES ];

void TERRENOsepara_sprites(){
	/* Corta os sprites da imagem */
    SPRITEterreno[ TERRENO_LESTE_ISO ].x = 0;
    SPRITEterreno[ TERRENO_LESTE_ISO ].y = 0;
    SPRITEterreno[ TERRENO_LESTE_ISO ].w = TERRENO_LARGURA;
    SPRITEterreno[ TERRENO_LESTE_ISO ].h = TERRENO_ALTURA;

    SPRITEterreno[ TERRENO_OESTE_ISO ].x = 0;
    SPRITEterreno[ TERRENO_OESTE_ISO ].y = 50;
    SPRITEterreno[ TERRENO_OESTE_ISO ].w = TERRENO_LARGURA;
    SPRITEterreno[ TERRENO_OESTE_ISO ].h = TERRENO_ALTURA;

    SPRITEterreno[ TERRENO_NORTE_ISO ].x = 0;
    SPRITEterreno[ TERRENO_NORTE_ISO ].y = 100;
    SPRITEterreno[ TERRENO_NORTE_ISO ].w = TERRENO_LARGURA;
    SPRITEterreno[ TERRENO_NORTE_ISO ].h = TERRENO_ALTURA;

    SPRITEterreno[ TERRENO_NOROESTE ].x = 50;
    SPRITEterreno[ TERRENO_NOROESTE ].y = 0;
    SPRITEterreno[ TERRENO_NOROESTE ].w = TERRENO_LARGURA;
    SPRITEterreno[ TERRENO_NOROESTE ].h = TERRENO_ALTURA;

    SPRITEterreno[ TERRENO_OESTE ].x = 50;
    SPRITEterreno[ TERRENO_OESTE ].y = 50;
    SPRITEterreno[ TERRENO_OESTE ].w = TERRENO_LARGURA;
    SPRITEterreno[ TERRENO_OESTE ].h = TERRENO_ALTURA;

    SPRITEterreno[ TERRENO_SUDOESTE ].x = 50;
    SPRITEterreno[ TERRENO_SUDOESTE ].y = 100;
    SPRITEterreno[ TERRENO_SUDOESTE ].w = TERRENO_LARGURA;
    SPRITEterreno[ TERRENO_SUDOESTE ].h = TERRENO_ALTURA;

    SPRITEterreno[ TERRENO_NORTE ].x = 100;
    SPRITEterreno[ TERRENO_NORTE ].y = 0;
    SPRITEterreno[ TERRENO_NORTE ].w = TERRENO_LARGURA;
    SPRITEterreno[ TERRENO_NORTE ].h = TERRENO_ALTURA;

    SPRITEterreno[ TERRENO_CENTRO ].x = 100;
    SPRITEterreno[ TERRENO_CENTRO ].y = 50;
    SPRITEterreno[ TERRENO_CENTRO ].w = TERRENO_LARGURA;
    SPRITEterreno[ TERRENO_CENTRO ].h = TERRENO_ALTURA;

    SPRITEterreno[ TERRENO_SUL ].x = 100;
    SPRITEterreno[ TERRENO_SUL ].y = 100;
    SPRITEterreno[ TERRENO_SUL ].w = TERRENO_LARGURA;
    SPRITEterreno[ TERRENO_SUL ].h = TERRENO_ALTURA;

    SPRITEterreno[ TERRENO_NORDESTE ].x = 150;
    SPRITEterreno[ TERRENO_NORDESTE ].y = 0;
    SPRITEterreno[ TERRENO_NORDESTE ].w = TERRENO_LARGURA;
    SPRITEterreno[ TERRENO_NORDESTE ].h = TERRENO_ALTURA;

    SPRITEterreno[ TERRENO_LESTE ].x = 150;
    SPRITEterreno[ TERRENO_LESTE ].y = 50;
    SPRITEterreno[ TERRENO_LESTE ].w = TERRENO_LARGURA;
    SPRITEterreno[ TERRENO_LESTE ].h = TERRENO_ALTURA;

    SPRITEterreno[ TERRENO_SUDESTE ].x = 150;
    SPRITEterreno[ TERRENO_SUDESTE ].y = 100;
    SPRITEterreno[ TERRENO_SUDESTE ].w = TERRENO_LARGURA;
    SPRITEterreno[ TERRENO_SUDESTE ].h = TERRENO_ALTURA;
	
	SPRITEterreno[ TERRENO_SUL_ISO ].x = 200;
    SPRITEterreno[ TERRENO_SUL_ISO ].y = 0;
    SPRITEterreno[ TERRENO_SUL_ISO ].w = TERRENO_LARGURA;
    SPRITEterreno[ TERRENO_SUL_ISO ].h = TERRENO_ALTURA;

    SPRITEterreno[ TERRENO_CENTRO_ISO ].x = 200;
    SPRITEterreno[ TERRENO_CENTRO_ISO ].y = 50;
    SPRITEterreno[ TERRENO_CENTRO_ISO ].w = TERRENO_LARGURA;
    SPRITEterreno[ TERRENO_CENTRO_ISO ].h = TERRENO_ALTURA;

    SPRITEterreno[ TERRENO_NULO ].x = 200;
    SPRITEterreno[ TERRENO_NULO ].y = 100;
    SPRITEterreno[ TERRENO_NULO ].w = TERRENO_LARGURA;
    SPRITEterreno[ TERRENO_NULO ].h = TERRENO_ALTURA;
}


terreno TERRENOinicializa( int x, int y, int tipoTerreno ){
	terreno tijolo = malloc(sizeof(struct terreninho));
	
	/* Armazena as coordenadas */
    tijolo->box.x = x;
    tijolo->box.y = y;

    /* Armazena dados para colisão */
    tijolo->box.w = TERRENO_LARGURA;
    tijolo->box.h = TERRENO_ALTURA;

    /* Armazena o tipo do terreno */
    tijolo->tipo = tipoTerreno;
	
	return tijolo;
}


void TERRENOshow(terreno tijolo, SDL_Surface* SUPERFICIEterreno, SDL_Surface* tela) {
	/* Mostra o terreno */
	aplica_superficie( tijolo->box.x, tijolo->box.y, SUPERFICIEterreno, tela, &SPRITEterreno[ tijolo->tipo ] );
}

terreno* TERRENOcria_mapa(int i) {
	terreno* tijolo = malloc(TOTAL_TERRENOS * sizeof(terreno));

    /* Coordenadas dos terrenos */
    int x = 0, y = 0;
	
	/* Contadores */
	int t, tipoTerreno = -1;
	
	/* Apontador para receber arquivo */
	FILE *arquivo = NULL;

    /* Abre o mapa */
	switch(i){
		case 1: arquivo = fopen( "mapas/mapa1.map" , "r"); break;
		case 2: arquivo = fopen( "mapas/mapa2.map" , "r"); break;
		case 3: arquivo = fopen( "mapas/mapa3.map" , "r"); break;
		case 4: arquivo = fopen( "mapas/mapa4.map" , "r"); break;
	}
	
    /* Se o mapa não pode ser aberto */
    if( arquivo == NULL ) return false;
	
    /* Inicializar os terrenos */
    for( t = 0; t < TOTAL_TERRENOS; t++, tipoTerreno = -1) {
	
        /* Lê tipo do terreno no arquivo */
		fscanf(arquivo, "%d", &tipoTerreno);
		

        /* Verifica se o número é válido */
        if( ( tipoTerreno >= 0 ) && ( tipoTerreno < TERRENO_SPRITES ) )
            tijolo[ t ] = TERRENOinicializa( x, y, tipoTerreno );

        /* Movemos a coordenada x para a próxima posição */
        x += TERRENO_LARGURA;

        /* Se ultrapassou a tela */
        if( x >= LARGURA_TELA )
        {
            /* Volta para trás */
            x = 0;

            /* Vai para a próxima linha */
            y += TERRENO_ALTURA;
        }
    }

    /* Fecha o arquivo */
    fclose(arquivo);


	
    /* Se o mapa foi carregado corretamente */
    return tijolo;
}