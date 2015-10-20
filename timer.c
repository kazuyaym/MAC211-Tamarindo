#include "SDL/SDL.h"
#include "timer.h"
#include <stdlib.h>

#define boolean int
#define true 1
#define false 0

Timer TIMERinicializa()
{
    Timer i = malloc(sizeof(struct timer));

	/* Inicializa as vari�veis */
    i->startTicks = 0;
    i->pausedTicks = 0;
    i->paused = false;
    i->started = false;
	
	return i;
}

void TIMERstart(Timer i)
{
    /* Starta o timer */
	i->started = true;

    /* Despausa o timer */
	i->paused = false;

	/* Armazena o hor�rio atual */
	i->startTicks = SDL_GetTicks();
}

void TIMERstop(Timer i)
{
    /* Pausa o timer */
    i->started = false;

    /* Despausa o timer */
    i->paused = false;
}

void TIMERpause(Timer i)
{
    /* Se o timer estiver correndo e n�o estiver pausado ainda */
    if( ( i->started == true ) && ( i->paused == false ) )
    {
        /* Pausa o timer */
        i->paused = true;

        /* Calcula os ticks pausados */
        i->pausedTicks = SDL_GetTicks() - i->startTicks;
    }
}

void TIMERunpause(Timer i)
{
    /* Se o timer est� pausado */
    if( i->paused == true )
    {
        /* Despausa o timer */
        i->paused = false;

        /* Reseta os ticks iniciais */
        i->startTicks = SDL_GetTicks() - i->pausedTicks;

        /* Reseta os ticks pausados */
        i->pausedTicks = 0;
    }
}

int TIMERverifica_ticks(Timer i)
{
    /* Se o timer est� correndo */
    if( i->started == true )
    {
        /* Se o timer est� pausado */
        if( i->paused == true )
        {
            /* Retorna o n�mero de ticks quando o timer foi pausado */
            return i->pausedTicks;
        }
        else
        {
            /* Retorna o tempo atual menos o tempo inicial */
            return SDL_GetTicks() - i->startTicks;
        }
    }

   /* Se o timer n�o estiver rodando */
    return 0;
}

boolean TIMERfoi_startado(Timer i)
{
    return i->started;
}

boolean TIMERfoi_pausado(Timer i)
{
    return i->paused;
}