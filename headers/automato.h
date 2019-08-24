#ifndef AUTOMATO_H_INCLUDED
#define AUTOMATO_H_INCLUDED

typedef struct transicao{
    char *conjunto;
    Transicao *proxima;
}Transicao;

typedef struct estado{
    Transicao *transicoes;
    int numTransicoes;
}Estado;

typedef struct maquinaEstados{
    char estadoAtual;
}MaquinaEstados;

MaquinaEstados iniciarAutomato();

#endif // AUTOMATO_H_INCLUDED