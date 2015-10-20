typedef struct monstrinho *inimigo;

struct monstrinho{
	int id;
	float xVel, yVel;
	SDL_Rect box;
	
	int x0, y0;
	int xSup, xInf, ySup, yInf;
	
	int direcao;
};

inimigo INIMIGOinicializa(int);
void INIMIGOshow(inimigo , SDL_Surface*, SDL_Surface*);
void INIMIGOmove(inimigo);
