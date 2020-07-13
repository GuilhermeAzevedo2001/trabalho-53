main.o: main.c
	gcc -o main.o -c main.c

cores.o: cores.c
	gcc -o cores.o -c cores.c

tabuleiro.o: tabuleiro.c
	gcc -o tabuleiro.o -c tabuleiro.c

usuario.o: usuario.c
	gcc -o usuario.o -c usuario.c

verificacao.o: verificacao.c
	gcc -o verificacao.o -c verificacao.c

main: main.o cores.o tabuleiro.o usuario.o verificacao.o

all: main

run: main
	./main 

clean: 
	@rm main.o cores.o tabuleiro.o usuario.o verificacao.o