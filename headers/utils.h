#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

int TAM_ASCII;
char LETRA;
char SEPARADOR;
char COMENTARIO;
char IDENTIFICADOR;
char NUMERO;
char OPERADOR;
char NULO;

void iniciarPalavrasReservadas(char **matriz);
void iniciarLetras(char *vetor);
void iniciarNumeros(char *vetor);
void iniciarOperadores(char *vetor);
void iniciarSeparadores(char *vetor);
void iniciarTabelaAscii(char *vetor);


#endif // UTILS_H_INCLUDED