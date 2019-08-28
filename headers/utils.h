#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include "../headers/automato.h"
#include "../headers/lexico.h"
#include <string.h>

extern int TAM_ASCII;
extern char LETRA[];
extern char SEPARADOR[];
extern char COMENTARIO[];
extern char IDENTIFICADOR[];
extern char NUMERO[];
extern char OPERADOR[];
extern char NULO;
extern int LINHA;
extern int COLUNA;
extern char BUFFER[];


//void iniciarPalavrasReservadas(char **matriz);
//void iniciarLetras(char *vetor);
//void iniciarNumeros(char *vetor);
//void iniciarOperadores(char *vetor);
//void iniciarSeparadores(char *vetor);
//void iniciarTabelaAscii(char *vetor);

void iniciarPalavrasReservadas(char **matriz);
int listaVazia(Estado *f);
void iniciarLista(Estado *aux);
void inserirLista(Estado *f, char *transicao, int proxEstado);

void iniciarListaToken(ListaToken *aux);
int listaVaziaToken(ListaToken *f);
void inserirListaToken(ListaToken *f, char *valor, char *valorBruto, int _linha, int _coluna);
void setEstadoFinal(MaquinaEstados *maquinaEstados, int estado);

#endif // UTILS_H_INCLUDED