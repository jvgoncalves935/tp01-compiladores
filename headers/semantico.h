#ifndef SEMANTICO_H_INCLUDED
#define SEMANTICO_H_INCLUDED

int consultarTabelaIdentificadores(char *identificador);

typedef struct identificador{
    char *nome;
    char *valor;
    char *tipo;
    int linha;
    int coluna;
    struct identificador *proxima;
    struct identificador *anterior;
}Identificador;

typedef struct tabelaIdentificadores{
    Identificador *primeira;
    Identificador *ultima;
    int numIdentificadores;
}TabelaIdentificadores;

#endif // SEMANTICO_H_INCLUDED