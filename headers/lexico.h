#ifndef LEXICO_H_INCLUDED
#define LEXICO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct token{
    char *valor;
    char *valorBruto;
    int linha;
    int coluna;
    struct token *proxima;
    struct token *anterior;
}Token;

typedef struct listaToken{
    Token *primeira;
    Token *ultima;
    int numTokens;
}ListaToken;

void analiseLexica(MaquinaEstados *maquinaEstados, char *arquivo, char *nomeArquivo);
void escreverArquivoTokens(FILE *arq, ListaToken *listaToken);

#endif // LEXICO_H_INCLUDED