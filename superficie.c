#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "superficie.h"

#define boolean int
#define true 1
#define false 0

SDL_Surface *carrega_imagem( char *nomeArquivo )
{
    /* A imagem que será carregada */
    SDL_Surface* imagemCarregada = NULL;

    /* A superficie otimizada que será utilizada */
    SDL_Surface* imagemOtimizada = NULL;

    /* Carrega imagem */
    imagemCarregada = IMG_Load( nomeArquivo );

    /* Se a imagem foi carregada */
    if( imagemCarregada != NULL )
    {
        /* Cria uma superficie otimizada */
        imagemOtimizada = SDL_DisplayFormat( imagemCarregada );

        /* Libera superficie antiga */
        SDL_FreeSurface( imagemCarregada );

        /* Se a superficie foi otimizada */
        if( imagemOtimizada != NULL )
        {
            /* Chroma key da superficie, verde e azul no maximo (255) */
            SDL_SetColorKey( imagemOtimizada, SDL_SRCCOLORKEY, SDL_MapRGB( imagemOtimizada->format, 0x00, 0xFF, 0xFF ) );
        }
    }

    /* Retorna a superficie otimizada */
    return imagemOtimizada;
}

void aplica_superficie( int x, int y, SDL_Surface* fonte, SDL_Surface* destino, SDL_Rect* clip )
{
    /* Mantem coordenadas */
    SDL_Rect coordenada;

    /* Pega coordenadas */
    coordenada.x = x;
    coordenada.y = y;

    /* Blita */
    SDL_BlitSurface( fonte, clip, destino, &coordenada );
}