#ifndef SINTATICO_H_INCLUDED
#define SINTATICO_H_INCLUDED

#include "../headers/automato.h"

void analiseSintatica(ListaToken *listaToken, ListaToken *listaTokenIdentificadores);
void consumirToken(ListaToken *listaToken);

#endif // SINTATICO_H_INCLUDED