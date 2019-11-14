#ifndef GERADOR_H_INCLUDED
#define GERADOR_H_INCLUDED

extern FILE *ARQ_ASSEMBLY;
extern char NOME_ARQ_ASSEMBLY[300];

void iniciarNomeArquivoAssembly(char *nome);
void iniciarArquivoAssembly();
void fecharArquivoAssembly();
void geradorPush(char *valor);
void geradorPop(char *valor);
int isArquivoAssemblyFechado();
void invalidarArquivoAssembly();
void geradorAdd(char *destino, char *op1, char *op2);
void geradorAddi(char *destino, char *op1, char *op2);
void geradorSub(char *destino, char *op1, char *op2);
void geradorSubi(char *destino, char *op1, char *op2);
void geradorMul(char *destino, char *op1, char *op2);
void geradorMuli(char *destino, char *op1, char *op2);

#endif // GERADOR_H_INCLUDED