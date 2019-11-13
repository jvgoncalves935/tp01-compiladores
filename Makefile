fileH = headers/
fileC = src/

objetos = main.o automato.o lexico.o utils.o sintatico.o semantico.o gerador.o

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

sintatico.o: $(fileH)sintatico.h $(fileC)sintatico.c
	gcc -c -g -Wall -O3 $(fileC)sintatico.c
	
semantico.o: $(fileH)semantico.h $(fileC)semantico.c
	gcc -c -g -Wall -O3 $(fileC)semantico.c
	
gerador.o: $(fileH)gerador.h $(fileC)gerador.c
	gcc -c -g -Wall -O3 $(fileC)gerador.c

clean:
	rm -rf *.o
