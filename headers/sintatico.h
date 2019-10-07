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

void verificarLinguagem(int cont);
void verificarFuncao(int cont);
void verificarTipo(int cont);
void verificarListaArg(int cont);
void verificarArg(int cont);
void verificarDeclaracao(int cont);
void verificarListaIdentificadores(int cont);
void verificarStatementFinal(int cont);
void verificarStatementFor(int cont);
void verificarStatementWhile(int cont);
void verificarExpressaoFinalMesmo(int cont);
void verificarStatementIf(int cont);
void verificarStatementEscopo(int cont);

void verificarStatement(int cont);
void verificarCondicao(int cont);
void verificarExpressao(int cont);
void verificarExpressaoFinal(int cont);
void verificarCondicaoLinha(int cont);
void verificarExpressaoLinha(int cont);


#endif // SINTATICO_H_INCLUDED