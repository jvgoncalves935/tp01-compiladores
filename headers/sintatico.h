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
int verificarStatement(int cont);
void verificarStatementFor(int cont);
void verificarStatementWhile(int cont);
void verificarExpressao(int cont);
void verificarExpressao02(int cont);
void verificarStatementIf(int cont);
void verificarStatementEscopo(int cont);
void verificarExpressaoOpcional(int cont);
void verificarParteElse(int cont);
void verificarListaStatement(int cont);
void verificarListaStatementLinha(int cont);
void verificarValorR(int cont);
void verificarValorRLinha(int cont);
void verificarComparacao(int cont);
void verificarMagnitude(int cont);
void verificarMagnitudeLinha(int cont);
void verificarTermo(int cont);
void verificarTermoLinha(int cont);
void verificarFator(int cont);

int isComparacao(Token *aux);
int isFator(Token *aux);
int isTipoDeclaracao(int cont);


#endif // SINTATICO_H_INCLUDED