#ifndef AUTOMATO_H_INCLUDED
#define AUTOMATO_H_INCLUDED

typedef struct transicao{
    char *conjunto;
    int proximoEstado;
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
    int estadoAtual;
    Estado *estados;
}MaquinaEstados;

void criarEstado(Estado *estado, int idEstado);
void adicionarTransicao(MaquinaEstados *maquinaEstados, int idTransicao, char *conjunto);
void iniciarAutomato(MaquinaEstados *maquinaEstados);

#endif // AUTOMATO_H_INCLUDED