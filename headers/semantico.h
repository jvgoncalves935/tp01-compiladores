#ifndef SEMANTICO_H_INCLUDED
#define SEMANTICO_H_INCLUDED


typedef struct identificador{
    char *nome;
    char *valor;
    char *tipo;
    int linha;
    int coluna;
    char *registrador;
    struct identificador *proxima;
    struct identificador *anterior;
}Identificador;

typedef struct tabelaIdentificadores{
    Identificador *primeira;
    Identificador *ultima;
    int numIdentificadores;
}TabelaIdentificadores;

extern TabelaIdentificadores *tabelaIdentificadores;

int consultarTabelaIdentificadores(char *identificador);
void printTabelaIdentificadores();
void alterarTabelaIdTipo(char *nome, char *tipo);
void alterarTabelaIdValor(char *nome, char *valor);
void alterarTabelaIdLinhaColuna(char *nome, int linha, int coluna);
Identificador *tabelaLinhaColunaVariavel(char *nome);

void warningsSemanticos();
void validarVariaveisInutilizadas();
char *descobrirTipo(char *valor);
int validarLetra(char valor);
int validarNumero(char valor);
int tipoValidoTabela(char *nome, char *tipo, int linha, int coluna);
int nomeRegistradorVariavel(char *nome, char *saida);


#endif // SEMANTICO_H_INCLUDED