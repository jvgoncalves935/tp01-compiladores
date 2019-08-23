fileH = headers/
fileC = src/

objetos = utils.o main.o

tp1:	$(objetos)
	gcc $(objetos) -o tp1

main.o:	$(fileC)main.c
	gcc -c -g -Wall -O3 $(fileC)main.c

utils.o:	$(fileH)utils.h	$(fileC)utils.c
	gcc -c -g -Wall -O3 $(fileC)utils.c

clean:
	rm -rf *.o
