#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/gerador.h"

FILE *ARQ_ASSEMBLY;
char *NOME_ARQ_ASSEMBLY;

void iniciarNomeArquivoAssembly(char *nome){
    char nomeArquivoTemp[300];
    char nomeArquivoFinal[300];
    int i;
    int j=0;
    int achou = 0;
    for(i=0;nome[i] != '\0';i++){
        if(nome[i] == '.'){
            break;
        }
        if(achou){
            nomeArquivoTemp[j] = nome[i];
            j++;
        }
        if(nome[i] == '/'){
            achou = 1;
        }
        
    }
    sprintf(nomeArquivoFinal,"%s%s%s","assembly/",nomeArquivoTemp,".asm");
    NOME_ARQ_ASSEMBLY = malloc((strlen(nomeArquivoFinal)+1)*sizeof(char));
    sprintf(NOME_ARQ_ASSEMBLY,"%s",nomeArquivoFinal);
    printf("%s\n",NOME_ARQ_ASSEMBLY);
}

void iniciarArquivoAssembly(){
    char aux[1024];
    sprintf(aux,"assembly/%s.asm",NOME_ARQ_ASSEMBLY);
    ARQ_ASSEMBLY = fopen(aux,"w");
}

void fecharArquivoAssembly(){
    fclose(ARQ_ASSEMBLY);
    free(NOME_ARQ_ASSEMBLY);
}

void geradorPush(char *valor){
    fprintf(ARQ_ASSEMBLY,"push %s\n",valor);
}

void geradorPop(char *valor){
    fprintf(ARQ_ASSEMBLY,"pop %s\n",valor);
}