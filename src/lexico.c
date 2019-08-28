#include "../headers/utils.h"
#include <stdio.h>
#include <stdlib.h>

void analiseLexica(MaquinaEstados *maquinaEstados, char *arquivo, char *nomeArquivo){
    int tamArquivo = strlen(arquivo);
    int posicao;
    int valido = 1;
    int i;
    strcpy(BUFFER,"\0");

    //Iniciar palavras reservadas
    char **palavras_reservadas = malloc(32*(sizeof(char *)));
    for(i=0;i<32;i++){
        palavras_reservadas[i] = malloc(15*sizeof(char));
    }

    iniciarPalavrasReservadas(palavras_reservadas);

    //Gerar string com o caminho do arquivo de saida
    char *nomeArquivo01 = strtok(nomeArquivo,"/");
    char nomeArquivo02[100];
    while(nomeArquivo01 != NULL){
        sprintf(nomeArquivo02,"%s",nomeArquivo01);
        nomeArquivo01 = strtok(NULL,"/");
    }
    char *nomeArquivo03 = strtok(nomeArquivo02,".");
    char nomeArquivoFinal[100];
    sprintf(nomeArquivoFinal,"%s%s%s","out/",nomeArquivo03,"_tabela.txt");

    //Inicializar lista de tokens
    ListaToken *listaToken = malloc(sizeof(ListaToken));
    iniciarListaToken(listaToken);
    
    //Funcionamento do automato e reconhecimento de tokens
    for(posicao = 0;posicao<tamArquivo;posicao++){
        alimentarMaquinaEstados(maquinaEstados,arquivo[posicao],&valido,palavras_reservadas,listaToken);
        
        
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
        identificarToken(maquinaEstados,palavras_reservadas,listaToken);
        //inserirListaToken(listaToken,"reservada",BUFFER,LINHA,COLUNA-(strlen(BUFFER)));
    }

    //Fim do arquivo mas o estado nao eh final
    if(maquinaEstados->estados[maquinaEstados->estadoAtual].final == 0){
        valido = 0;
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
    char teste[100];
    while(aux != NULL){
        sprintf(teste,"%s",aux->valorBruto);
        if(!strcmp(teste,"\n")){
           sprintf(teste,"\\n"); 
        }
        if(!strcmp(teste,"\t")){
           sprintf(teste,"\\t"); 
        }
        fprintf(arq,"%s,\"%s\",%d,%d\n",aux->valor,teste,aux->linha,aux->coluna);
        aux = aux->proxima;
    }
}

int isPalavraReservada(char *str, char **palavrasReservadas){
    int i;
    for(i=0;i<32;i++){
        if(!strcmp(str,palavrasReservadas[i])){
            return 1;
        }
    }
    return 0;
}

void identificarToken(MaquinaEstados *maquinaEstados, char **palavrasReservadas, ListaToken *listaToken){
    if(maquinaEstados->estados[maquinaEstados->estadoAtual].final == 1){
        int achou = 0;
        char tipo[50];
        
        printf("%s\n",BUFFER);
        //Identificacao de tipo de token
        if(!achou && strchr(SEPARADOR,BUFFER[0]) != NULL){
            sprintf(tipo,"%s","separador");
            achou = 1; 
        }
    
        
        if(!achou && isPalavraReservada(BUFFER,palavrasReservadas)){
            sprintf(tipo,"%s","reservada");
            achou = 1;
        }
        
        if(!achou){
            sprintf(tipo,"%s","identificador");
        }
        inserirListaToken(listaToken,tipo,BUFFER,LINHA,COLUNA-(strlen(BUFFER)));
        
        strcpy(BUFFER,"\0");
    }
}