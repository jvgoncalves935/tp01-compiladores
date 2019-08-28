#ifndef LEXICO_H_INCLUDED
#define LEXICO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "../headers/automato.h"



void analiseLexica(MaquinaEstados *maquinaEstados, char *arquivo, char *nomeArquivo);
void escreverArquivoTokens(FILE *arq, ListaToken *listaToken);
int isPalavraReservada(char *str, char **palavrasReservadas);
void identificarToken(MaquinaEstados *maquinaEstados, char **palavrasReservadas, ListaToken *listaToken);

#endif // LEXICO_H_INCLUDED