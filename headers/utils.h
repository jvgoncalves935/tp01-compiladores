#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include "../headers/automato.h"
#include <string.h>

extern int TAM_ASCII;
extern char LETRA[];
extern char SEPARADOR[];
extern char COMENTARIO[];
extern char IDENTIFICADOR[];
extern char NUMERO[];
extern char OPERADOR[];
extern char NULO;

//void iniciarPalavrasReservadas(char **matriz);
//void iniciarLetras(char *vetor);
//void iniciarNumeros(char *vetor);
//void iniciarOperadores(char *vetor);
//void iniciarSeparadores(char *vetor);
//void iniciarTabelaAscii(char *vetor);

int listaVazia(Estado *f);
void iniciarLista(Estado *aux);
void inserirLista(Estado *f, char *transicao, int tamTransicao, int proxEstado);

#endif // UTILS_H_INCLUDED