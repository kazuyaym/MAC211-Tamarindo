all: main.o superficie.o inimigo.o barco.o timer.o mapa.o botao.o
	gcc -o Tamarindo main.o superficie.o inimigo.o barco.o timer.o mapa.o botao.o -lmingw32 -lSDLmain -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -mwindows

main.o: main.c
	gcc -c main.c

superficie.o: superficie.c
	gcc -c superficie.c
	
barco.o: barco.c
	gcc -c barco.c
	
timer.o: timer.c
	gcc -c timer.c
	
inimigo.o: inimigo.c
	gcc -c inimigo.c

mapa.o: mapa.c
	gcc -c mapa.c

botao.o: botao.c
	gcc -c botao.c