typedef struct botaozinho *botao;

struct botaozinho{
	int ind;

	SDL_Rect box;
};


void BOTAOsepara_sprites();
botao BOTAOinicializa();
void BOTAOgerencia_evento(botao, SDL_Event);
void BOTAOshow( botao, SDL_Surface*, SDL_Surface*);