#ifndef LEXICO_H_INCLUDED
#define LEXICO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "../headers/automato.h"



void analiseLexica(MaquinaEstados *maquinaEstados, char *arquivo, char *nomeArquivo);
void escreverArquivoTokens(FILE *arq, ListaToken *listaToken);
int isPalavraReservada(char *str, char **palavrasReservadas);
void identificarToken(MaquinaEstados *maquinaEstados, char **palavrasReservadas, ListaToken *listaToken);
int isNumero(char *str);
char *tipoSeparador(char str);
int isOperador(char *str);
void iniciarMensagensErro(MaquinaEstados *maquinaEstados);
void adicionarMensagemErro(MaquinaEstados *maquinaEstados, char *mensagem, int estado);
int isLiteralAspasDuplas(char *str);

#endif // LEXICO_H_INCLUDED