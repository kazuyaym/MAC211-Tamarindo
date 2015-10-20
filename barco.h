typedef struct barquinho *barco;

struct barquinho{
	SDL_Rect box;
	int anda;
	int xVel, yVel;
	int direcao, rotacao;
	int vida;
};

barco BARCOinicializa();
void BARCOverifica_movimento(barco, SDL_Event);
void BARCOmove(barco, terreno*);
void BARCOshow(barco, SDL_Surface*, SDL_Surface*);
int BARCOverifica_colisao(SDL_Rect, SDL_Rect);