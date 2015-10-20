typedef struct terreninho *terreno;

struct terreninho{
	//The attributes of the tile
	SDL_Rect box;

    //The tile type
    int tipo;
};

void TERRENOsepara_sprites();
terreno TERRENOinicializa( int, int, int );
void TERRENOshow(terreno, SDL_Surface* , SDL_Surface* );
terreno* TERRENOcria_mapa();