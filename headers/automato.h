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
    int final;
    Transicao *primeira;
    Transicao *ultima;
    int numTransicoes;
}Estado;

typedef struct maquinaEstados{
    //Trocar pra int
    int estadoAtual;
    Estado *estados;
}MaquinaEstados;

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

void criarEstado(Estado *estado, int idEstado);
void adicionarTransicao(MaquinaEstados *maquinaEstados, int idTransicao, char *conjunto);
void iniciarAutomato(MaquinaEstados *maquinaEstados);
void alimentarMaquinaEstados(MaquinaEstados *maquinaEstados, char token, int *valido, char **palavrasReservadas, ListaToken *listaToken);

#endif // AUTOMATO_H_INCLUDED