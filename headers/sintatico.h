#ifndef SINTATICO_H_INCLUDED
#define SINTATICO_H_INCLUDED

#include "../headers/automato.h"
#include "../headers/utils.h"

void analiseSintatica(ListaToken *listaTokenIdentificadores);
void consumirToken(int cont);
int tokenIgual(Token *token, char *str);
int tokenDiferente(Token *token, char *str);
void erroSintatico(Token *token, char *erro);
Token *getToken();
void printfSintatico(int cont, char *str);

void verificarCondicaoInicial(int cont);
void verificarCondicao(int cont);
void verificarExpressao(int cont);
void verificarExpressaoFinal(int cont);
void verificarCondicaoLinha(int cont);
void verificarExpressaoLinha(int cont);


#endif // SINTATICO_H_INCLUDED