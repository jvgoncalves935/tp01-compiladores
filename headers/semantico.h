#ifndef SEMANTICO_H_INCLUDED
#define SEMANTICO_H_INCLUDED

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

int consultarTabelaIdentificadores(TabelaIdentificadores *tabela, char *identificador);
void printTabelaIdentificadores(TabelaIdentificadores *tabela);

#endif // SEMANTICO_H_INCLUDED