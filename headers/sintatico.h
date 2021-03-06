#ifndef SINTATICO_H_INCLUDED
#define SINTATICO_H_INCLUDED

#include "../headers/automato.h"
#include "../headers/utils.h"
#include "../headers/semantico.h"
#include "../headers/gerador.h"

void analiseSintatica(ListaToken *listaTokenIdentificadores);
void preencherTabelaIdentificadores(ListaToken *listaTokenIdentificadores);
void consumirToken(int cont);
int tokenIgual(Token *token, char *str);
int tokenDiferente(Token *token, char *str);
void erroSintatico(Token *token, char *erro);
Token *getToken();
void printfSintatico(int cont, char *str);
void proximoPontoVirgula();
void erroSemantico(Token *token, char *erro);

int verificarListaDiretivas(int cont);
int verificarLinguagem(int cont);
int verificarFuncao(int cont);
int verificarTipo(int cont, char *tipo);
int verificarListaArg(int cont);
int verificarArg(int cont);
int verificarDeclaracao(int cont);
int verificarListaIdentificadores(int cont, char *tipo);
int verificarStatement(int cont);
int verificarStatementFor(int cont);
int verificarStatementWhile(int cont);
int verificarStatementReturn(int cont);
int verificarExpressao(int cont, char *iden);
int verificarExpressao02(int cont,char *iden);
int verificarStatementIf(int cont);
int verificarStatementEscopo(int cont);
int verificarExpressaoOpcional(int cont);
int verificarParteElse(int cont);
int verificarListaStatement(int cont);
int verificarListaStatementLinha(int cont);
int verificarValorR(int cont, char *iden);
int verificarValorRLinha(int cont, char *iden);
int verificarComparacao(int cont);
int verificarMagnitude(int cont, char *iden);
int verificarMagnitudeLinha(int cont, char *iden);
int verificarTermo(int cont, char *iden);
int verificarTermoLinha(int cont, char *iden);
int verificarFator(int cont, char *iden);
int verificarAritmetica(int cont);
int verificarAritmeticaOperadorDuplicado(int cont);
int verificarAritmeticaOperadorIgualComposto(int cont);
int verificarStatementDoWhile(int cont);
int verificarSwitch01(int cont);
int verificarSwitch02(int cont);
int verificarListaCase(int cont);
int verificarListaCaseLinha(int cont);
int verificarChamadaFuncao(int cont);
int verificarListaArgChamadaFuncao(int cont);
int verificarListaArgChamadaFuncaoLinha(int cont);

int isAritmetica(Token *aux);
int isComparacao(Token *aux);
int isFator(Token *aux);
int isTipoDeclaracao(Token *aux);
int isAritmeticaOperadorDuplicado(Token *aux);
int isAritmeticaOperadorIgualComposto(Token *aux);

void geradorSintPush(char *iden);
void geradorSintPop(char *iden);

#endif // SINTATICO_H_INCLUDED