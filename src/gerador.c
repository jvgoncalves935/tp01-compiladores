#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/gerador.h"

FILE *ARQ_ASSEMBLY;
char NOME_ARQ_ASSEMBLY[300];

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
    //NOME_ARQ_ASSEMBLY = malloc((strlen(nomeArquivoFinal)+1)*sizeof(char));
    sprintf(NOME_ARQ_ASSEMBLY,"%s",nomeArquivoFinal);
    //printf("%s\n",NOME_ARQ_ASSEMBLY);
}

void iniciarArquivoAssembly(){
    //char aux[1024];
    //sprintf(aux,"assembly/%s.asm",NOME_ARQ_ASSEMBLY);
    ARQ_ASSEMBLY = fopen(NOME_ARQ_ASSEMBLY,"w");
}

void fecharArquivoAssembly(){
    if(!isArquivoAssemblyFechado()){
        if(fclose(ARQ_ASSEMBLY) == 0){
            ARQ_ASSEMBLY = NULL;
        }
    }    
    //free(NOME_ARQ_ASSEMBLY);
}

int isArquivoAssemblyFechado(){
    return ARQ_ASSEMBLY == NULL;
}

void invalidarArquivoAssembly(){
    fecharArquivoAssembly();
    iniciarArquivoAssembly();
    fecharArquivoAssembly();
}

void geradorPush(char *valor){
    if(isArquivoAssemblyFechado()){
        return;
    }
    fprintf(ARQ_ASSEMBLY,"push %s\n",valor);
}

void geradorPop(char *valor){
    if(isArquivoAssemblyFechado()){
        return;
    }
    fprintf(ARQ_ASSEMBLY,"pop %s\n",valor);
}

void geradorAdd(char *destino, char *op1, char *op2){
    if(isArquivoAssemblyFechado()){
        return;
    }
    fprintf(ARQ_ASSEMBLY,"add %s %s %s\n",destino,op1,op2);
}

void geradorAddi(char *destino, char *op1, char *op2){
    if(isArquivoAssemblyFechado()){
        return;
    }
    fprintf(ARQ_ASSEMBLY,"addi %s %s %s\n",destino,op1,op2);
}

void geradorSub(char *destino, char *op1, char *op2){
    if(isArquivoAssemblyFechado()){
        return;
    }
    fprintf(ARQ_ASSEMBLY,"sub %s %s %s\n",destino,op1,op2);
}

void geradorSubi(char *destino, char *op1, char *op2){
    if(isArquivoAssemblyFechado()){
        return;
    }
    fprintf(ARQ_ASSEMBLY,"subi %s %s %s\n",destino,op1,op2);
}

void geradorMul(char *destino, char *op1, char *op2){
    if(isArquivoAssemblyFechado()){
        return;
    }
    fprintf(ARQ_ASSEMBLY,"mul %s %s %s\n",destino,op1,op2);
}

void geradorMuli(char *destino, char *op1, char *op2){
    if(isArquivoAssemblyFechado()){
        return;
    }
    fprintf(ARQ_ASSEMBLY,"muli %s %s %s\n",destino,op1,op2);
}
