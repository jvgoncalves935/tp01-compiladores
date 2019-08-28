#include "../headers/utils.h"
#include <stdio.h>
#include <stdlib.h>

void analiseLexica(MaquinaEstados *maquinaEstados, char *arquivo, char *nomeArquivo){
    int tamArquivo = strlen(arquivo);
    int posicao;
    int valido = 1;
    strcpy(BUFFER,"\0");

    //Gerar string com o caminho do arquivo de saida
    char *nomeArquivo01 = strtok(nomeArquivo,"/");
    char nomeArquivo02[100];
    while(nomeArquivo01 != NULL){
        /* code */
        sprintf(nomeArquivo02,"%s",nomeArquivo01);
        
        nomeArquivo01 = strtok(NULL,"/");
    }
    char *nomeArquivo03 = strtok(nomeArquivo02,".");
    char nomeArquivoFinal[100];
    sprintf(nomeArquivoFinal,"%s%s%s","out/",nomeArquivo03,"_tabela.txt");

    ListaToken *listaToken = malloc(sizeof(ListaToken));
    iniciarListaToken(listaToken);
    
    for(posicao = 0;posicao<tamArquivo;posicao++){
        alimentarMaquinaEstados(maquinaEstados,arquivo[posicao],&valido);
        if(maquinaEstados->estados[maquinaEstados->estadoAtual].final == 1){
            inserirListaToken(listaToken,"reservada",BUFFER,LINHA,COLUNA-(strlen(BUFFER)));
            printf("%s\n",BUFFER);
            strcpy(BUFFER,"\0");
        }
        if(!valido){
            break;
        }
        if(arquivo[posicao] != '\n'){
            COLUNA++;
        }else{
            LINHA++;
            COLUNA = 1;
        }
    }

    //O buffer ainda não está vazio
    if(strlen(BUFFER) > 0){
        inserirListaToken(listaToken,"reservada",BUFFER,LINHA,COLUNA-(strlen(BUFFER)));
    }

    if(valido){
        printf("\nAnalise Lexica: SUCESSO.\n");
        FILE *arq = fopen(nomeArquivoFinal,"w");
        escreverArquivoTokens(arq,listaToken);
        fclose(arq);
    }else{
        printf("\nAnalise Lexica: ERRO. Linha %d, Coluna %d.\n",LINHA,COLUNA);
    }
}

void escreverArquivoTokens(FILE *arq, ListaToken *listaToken){
    Token *aux = listaToken->primeira;
    while(aux != NULL){
        fprintf(arq,"%s,\"%s\",%d,%d\n",aux->valor,aux->valorBruto,aux->linha,aux->coluna);
        aux = aux->proxima;
    }
}
