#include <stdio.h>
#include <stdlib.h>
#include "../headers/sintatico.h"

void analiseSintatica(ListaToken *listaTokenIdentificadores){
    
    while(LISTATOKEN->primeira != NULL){
        //Token *aux = NULL;
        Token *aux = consumirToken();
        printf("Consumir Token %s\n",aux->valorBruto);
        freePosicao(aux);
        
    }

    if(LISTATOKEN->primeira == NULL){
        //freePosicao(LISTATOKEN->primeira);
        free(LISTATOKEN);
        printf("Analise Sintatica: SUCESSO.\n");
    }else{
        //printf("come vaiem %s\n",LISTATOKEN->primeira->valorBruto);
        printf("Analise Sintatica: ERRO.\n");
    }
    
    //freeLISTATOKEN(LISTATOKEN);
    //freeLISTATOKEN(LISTATOKENIdentificadores);
}

Token *consumirToken(){
    Token *tok = NULL;
    if(LISTATOKEN == NULL){
        printf("Lista de tokens vazia!");
        return tok;
    }

    Token *aux = LISTATOKEN->primeira;
    tok = aux;
    
    //memcpy(tok,aux,sizeof(Token));
    if(aux == NULL){
        printf("Lista de tokens vazia!");
        return tok;
    }

    

    if(LISTATOKEN->primeira->proxima != NULL){
        LISTATOKEN->primeira = LISTATOKEN->primeira->proxima;
        LISTATOKEN->primeira->anterior = NULL;
    }else{
        
        LISTATOKEN->primeira = NULL;
        //return NULL;
    }

    //printf("Consumir Token %s\n",aux->valorBruto);

    return tok;
}

void freePosicao(Token *aux){
    free(aux->valor);
    free(aux->valorBruto);
    free(aux);
}