#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "superficie.h"
#include "botao.h"

#define LARGURA_TELA 800
#define ALTURA_TELA 600

#define BOTAO_MOUSEOVER 0
#define BOTAO_MOUSEOUT 1
#define BOTAO_MOUSEDOWN 2
#define BOTAO_MOUSEUP 3

#define LARGURA_BOTAO 283
#define ALTURA_BOTAO 23


SDL_Rect SPRITEbotao[3];

void BOTAOsepara_sprites(){
    SPRITEbotao[ BOTAO_MOUSEOVER ].x = 0;
    SPRITEbotao[ BOTAO_MOUSEOVER ].y = 0;
    SPRITEbotao[ BOTAO_MOUSEOVER ].w = LARGURA_BOTAO;
    SPRITEbotao[ BOTAO_MOUSEOVER ].h = ALTURA_BOTAO;

    SPRITEbotao[ BOTAO_MOUSEOUT ].x = 0;
    SPRITEbotao[ BOTAO_MOUSEOUT ].y = 28;
    SPRITEbotao[ BOTAO_MOUSEOUT ].w = LARGURA_BOTAO;
    SPRITEbotao[ BOTAO_MOUSEOUT ].h = ALTURA_BOTAO;

    SPRITEbotao[ BOTAO_MOUSEDOWN ].x = 0;
    SPRITEbotao[ BOTAO_MOUSEDOWN ].y = 56;
    SPRITEbotao[ BOTAO_MOUSEDOWN ].w = LARGURA_BOTAO;
    SPRITEbotao[ BOTAO_MOUSEDOWN ].h = ALTURA_BOTAO;
	
	SPRITEbotao[ BOTAO_MOUSEUP ].x = 0;
    SPRITEbotao[ BOTAO_MOUSEUP ].y = 28;
    SPRITEbotao[ BOTAO_MOUSEUP ].w = LARGURA_BOTAO;
    SPRITEbotao[ BOTAO_MOUSEUP ].h = ALTURA_BOTAO;
}


botao BOTAOinicializa(){
	botao i = malloc(sizeof(struct botaozinho));
	
	i->box.w = LARGURA_BOTAO;
	i->box.h = ALTURA_BOTAO;
	i->ind = 1;
	
	return i;
}


void BOTAOgerencia_evento(botao i, SDL_Event event) {
    /* Coordenadas do mouse */
    int x = 0, y = 0;

    /* Se o mouse se moveu */
    if( event.type == SDL_MOUSEMOTION )
    {
        /* Pega as coordenadas do mouse */
        x = event.motion.x;
        y = event.motion.y;

        /* Se o mouse está sobre o botão */
        if( ( x > i->box.x ) && ( x < i->box.x + i->box.w ) && ( y > i->box.y ) && ( y < i->box.y + i->box.h ) )
        {
            /* Aplica o sprite do botão em mouseover */
            i->ind = BOTAO_MOUSEOVER;
        }
        /* Senão */
        else
        {
            /* Aplica o sprite do botão em mouseout */
            i->ind = BOTAO_MOUSEOUT;
        }
    }
    /* Se o botão do mouse foi pressionado */
    if( event.type == SDL_MOUSEBUTTONDOWN )
    {
        /* Se o botão esquerdo foi pressionado */
        if( event.button.button == SDL_BUTTON_LEFT )
        {
            /* Pega as coordenadas do mouse */
            x = event.button.x;
            y = event.button.y;

            /* Se o mouse está sobre o botão */
            if( ( x > i->box.x ) && ( x < i->box.x + i->box.w ) && ( y > i->box.y ) && ( y < i->box.y + i->box.h ) )
            {
                /* Aplica o sprite do botão em mousedown */
                i->ind = BOTAO_MOUSEDOWN;
            }
        }
    }
	/* Se o botão do mouse foi solto */
    if( event.type == SDL_MOUSEBUTTONUP )
    {
        //If the left mouse button was released
        if( event.button.button == SDL_BUTTON_LEFT )
        {
            //Get the mouse offsets
            x = event.button.x;
            y = event.button.y;

            //If the mouse is over the button
            if( ( x > i->box.x ) && ( x < i->box.x + i->box.w ) && ( y > i->box.y ) && ( y < i->box.y + i->box.h ) )
            {
                /* Aplica o sprite do botão em mousedown */
                i->ind = BOTAO_MOUSEUP;
            }
        }
    }
}

void BOTAOshow( botao i, SDL_Surface* SUPERFICIEbotao, SDL_Surface* tela) {
    /* Exibe o botão */
    aplica_superficie( i->box.x, i->box.y, SUPERFICIEbotao, tela, &SPRITEbotao[i->ind] );
}