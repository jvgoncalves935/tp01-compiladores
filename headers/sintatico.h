#ifndef SINTATICO_H_INCLUDED
#define SINTATICO_H_INCLUDED

#include "../headers/automato.h"
#include "../headers/utils.h"

void analiseSintatica(ListaToken *listaTokenIdentificadores);
Token *consumirToken();
void freePosicao(Token *aux);

#endif // SINTATICO_H_INCLUDED