fileH = headers/
fileC = src/

objetos = automato.o utils.o lexico.o main.o

tp1:	$(objetos)
	gcc $(objetos) -o tp1

main.o:	$(fileC)main.c
	gcc -c -g -Wall -O3 $(fileC)main.c

utils.o:	$(fileH)utils.h	$(fileC)utils.c
	gcc -c -g -Wall -O3 $(fileC)utils.c
	
lexico.o:	$(fileH)lexico.h $(fileC)lexico.c
	gcc -c -g -Wall -O3 $(fileC)lexico.c
	
automato.o:	$(fileH)automato.h $(fileC)automato.c
	gcc -c -g -Wall -O3 $(fileC)automato.c

clean:
	rm -rf *.o
