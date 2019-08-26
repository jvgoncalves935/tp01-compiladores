#ifndef AUTOMATO_H_INCLUDED
#define AUTOMATO_H_INCLUDED

typedef struct transicao{
    char *conjunto;
    struct transicao *proxima;
    struct transicao *anterior;
}Transicao;

typedef struct estado{
    int id;
    Transicao *primeira;
    Transicao *ultima;
    int numTransicoes;
}Estado;

typedef struct maquinaEstados{
    //Trocar pra int
    char estadoAtual;
    Estado *estados;
}MaquinaEstados;

MaquinaEstados iniciarAutomato();

void adicionarTransicao(int idTransicao, char *conjunto);

#endif // AUTOMATO_H_INCLUDED