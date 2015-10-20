#define boolean int

typedef struct timer* Timer;

struct timer {
	int startTicks;
	int pausedTicks;

	boolean paused;
	boolean started;
};

Timer TIMERinicializa();
void TIMERstart(Timer i);
void TIMERstop(Timer i);
void TIMERpause(Timer i);
void TIMERunpause(Timer i);
int TIMERverifica_ticks(Timer i);
boolean TIMERfoi_startado(Timer i);
boolean TIMERfoi_pausado(Timer i);
