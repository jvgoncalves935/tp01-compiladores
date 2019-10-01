#include <stdio.h>
#include <stdlib.h>
#include "../headers/sintatico.h"

void analiseSintatica(ListaToken *listaToken, ListaToken *listaTokenIdentificadores){
    
    while(listaToken->primeira != NULL){
        consumirToken(listaToken);
    }

    if(listaToken->primeira == NULL){
        free(listaToken);
        printf("Analise Sintatica: SUCESSO.\n");
    }else{
        printf("Analise Sintatica: ERRO.\n");
    }
    
    //freeListaToken(listaToken);
    //freeListaToken(listaTokenIdentificadores);
}

void consumirToken(ListaToken *listaToken){
    if(listaToken == NULL){
        printf("Lista de tokens vazia!");
        return;
    }

    Token *aux = listaToken->primeira;
    if(aux == NULL){
        printf("Lista de tokens vazia!");
        return;
    }

    if(listaToken->primeira->proxima != NULL){
        listaToken->primeira = listaToken->primeira->proxima;
        listaToken->primeira->anterior = NULL;
    }else{
        listaToken->primeira = NULL;
    }

    //printf("Consumir Token %s\n",aux->valorBruto);

    free(aux->valor);
    free(aux->valorBruto);
    free(aux);
}