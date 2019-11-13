#ifndef GERADOR_H_INCLUDED
#define GERADOR_H_INCLUDED

extern FILE *ARQ_ASSEMBLY;
extern char *NOME_ARQ_ASSEMBLY;

void iniciarNomeArquivoAssembly(char *nome);
void iniciarArquivoAssembly();
void fecharArquivoAssembly();
void geradorPush(char *valor);
void geradorPop(char *valor);

#endif // GERADOR_H_INCLUDED