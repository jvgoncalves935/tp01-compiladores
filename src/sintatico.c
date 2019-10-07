#include <stdio.h>
#include <stdlib.h>
#include "../headers/sintatico.h"

void analiseSintatica(ListaToken *listaTokenIdentificadores){
    
    //while(LISTATOKEN->primeira != NULL){
        //Token *aux = NULL;
        /*
        Token *aux = consumirToken();
        printf("Consumir Token %s\n",aux->valorBruto);
        freePosicao(aux);
        */
    //}
    verificarLinguagem(0);

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

Token *getToken(){
    if(!FLAG_SINTATICO){
        return NULL;
    }
    if(LISTATOKEN == NULL){
        //printf("Lista de tokens vazia!");
        FLAG_SINTATICO = 0;
        return NULL;
    }

    Token *aux = LISTATOKEN->primeira;
    //memcpy(tok,aux,sizeof(Token));
    if(aux == NULL){
        //printf("Lista de tokens vazia!");
        FLAG_SINTATICO = 0;
        return NULL;
    }

    return aux;
}

void consumirToken(int cont){
    if(!FLAG_SINTATICO){
        return;
    }
    if(LISTATOKEN == NULL){
        //printf("Lista de tokens vazia!");
        FLAG_SINTATICO = 0;
        return;
    }

    Token *aux = LISTATOKEN->primeira;
    
    //memcpy(tok,aux,sizeof(Token));
    if(aux == NULL){
        //printf("Lista de tokens vazia!");
        FLAG_SINTATICO = 0;
        return;
    }

    if(LISTATOKEN->primeira->proxima != NULL){
        LISTATOKEN->primeira = LISTATOKEN->primeira->proxima;
        LISTATOKEN->primeira->anterior = NULL;
    }else{
        
        LISTATOKEN->primeira = NULL;
        //return NULL;
    }

    //printf("Consumir Token %s\n",aux->valorBruto);
    printfSintatico(cont,aux->valorBruto);

    free(aux->valor);
    free(aux->valorBruto);
    free(aux);
}

void printfSintatico(int cont, char *str){
    char aux[1024];
    sprintf(aux,"%c",'\0');
    int i;
    for(i=0;i<cont;i++){
        sprintf(aux,"%s  ",aux);
    }
    printf("%s%s\n",aux,str);
    getchar();
}

int tokenIgual(Token *token, char *str){
    if(!FLAG_SINTATICO){
        return 0;
    }
    return !strcmp(token->valor,str);
}

int tokenDiferente(Token *token, char *str){
    if(!FLAG_SINTATICO){
        return 0;
    }
    return strcmp(token->valor,str);
}

void erroSintatico(Token *token, char *erro){
    if(!FLAG_SINTATICO){
        return;
    }
    printf("Analise Sintatica: ERRO. %s Linha %d, Coluna %d\n",erro,token->linha,token->coluna);
    exit(0);
}

void verificarLinguagem(int cont){
    while(LISTATOKEN->primeira != NULL){
        printfSintatico(cont,"verificarLinguagem");
        verificarFuncao(cont+1);
    }
}

void verificarFuncao(int cont){
    printfSintatico(cont,"verificarFuncao");
    verificarTipo(cont+1);

    Token *aux = getToken();
    if(tokenIgual(aux,"identificador")){
        consumirToken(cont);
    }else{
        erroSintatico(aux,"Expressao invalida em declaracao de funcao (era esperado um identificador).");
    }

    aux = getToken();
    if(tokenIgual(aux,"abre_parenteses")){
        consumirToken(cont);
    }else{
        erroSintatico(aux,"Expressao invalida em declaracao de funcao (era esperado um abre_parenteses).");
    }

    verificarListaArg(cont+1);

    aux = getToken();
    if(tokenIgual(aux,"fecha_parenteses")){
        consumirToken(cont);
    }else{
        erroSintatico(aux,"Expressao invalida em declaracao de funcao (era esperado um fecha_parenteses).");
    }

    aux = getToken();
    if(tokenIgual(aux,"abre_chaves")){
        consumirToken(cont);
    }else{
        erroSintatico(aux,"Expressao invalida em declaracao de funcao (era esperado um abre_chaves).");
    }

    aux = getToken();
    if(tokenIgual(aux,"fecha_chaves")){
        consumirToken(cont);
    }else{
        erroSintatico(aux,"Expressao invalida em declaracao de funcao (era esperado um fecha_chaves).");
    }
    
    //verificarStatement(cont+1);
}

void verificarTipo(int cont){
    printfSintatico(cont,"verificarTipo");
    Token *aux = getToken();
    if(tokenIgual(aux,"int")){
        consumirToken(cont); return;
    }
    if(tokenIgual(aux,"float")){
        consumirToken(cont); return;
    }
    if(tokenIgual(aux,"char")){
        consumirToken(cont); return;
    }
    if(tokenIgual(aux,"double")){
        consumirToken(cont); return;
    }
    erroSintatico(aux,"Tipo invalido para funcao.");
    
}

void verificarListaArg(int cont){
    printfSintatico(cont,"verificarListaArg");
    verificarArg(cont+1);
    if(strcmp(LISTATOKEN->primeira->valor,"virgula")){
        return;
    }

    Token *aux = getToken();
    if(tokenIgual(aux,"virgula")){
        consumirToken(cont);
    }else{
        erroSintatico(aux,"Expressao invalida em parametro de funcao (era esperado uma virgula).");
    }

    verificarListaArg(cont+1);


}

void verificarArg(int cont){
    printfSintatico(cont,"verificarArg");
    verificarTipo(cont+1);

    Token *aux = getToken();
    if(tokenIgual(aux,"identificador")){
        consumirToken(cont);
    }else{
        erroSintatico(aux,"Expressao invalida em parametro de funcao (era esperado um identificador).");
    }
}

void verificarDeclaracao(int cont){
    printfSintatico(cont,"verificarDeclaracao");
    verificarTipo(cont+1);
    verificarListaIdentificadores(cont+1);

}

void verificarListaIdentificadores(int cont){
    printfSintatico(cont,"verificarListaIdentificadores");

    Token *aux = getToken();
    if(tokenIgual(aux,"identificador")){
        consumirToken(cont);
    }else{
        erroSintatico(aux,"Expressao invalida em declaracao (era esperado um identificador).");
    }
    aux = getToken();
    if(tokenIgual(aux,"virgula")){
        consumirToken(cont);
        verificarListaIdentificadores(cont+1);
    }
}

void verificarStatementFinal(int cont){
    printfSintatico(cont,"verificarStatementFinal");
    Token *aux = getToken();

    if(tokenIgual(aux,"for")){
        verificarStatementFor(cont+1);
        return;
    }
    if(tokenIgual(aux,"while")){
        verificarStatementWhile(cont+1);
        return;
    }
    //FAZER O EXPRESSAOFINALMESMO
    if(tokenIgual(aux,"if")){
        verificarStatementIf(cont+1);
        return;
    }
    if(tokenIgual(aux,"abre_chaves")){
        verificarStatementEscopo(cont+1);
        return;
    }
    //FAZER O DECLARACAO
    if(tokenIgual(aux,"ponto_virgula")){
        consumirToken(cont);
        return;
    }

    //Erro no statement
    erroSintatico(aux,"Expressao invalida em statement.");
}

void verificarStatementFor(int cont){
    printfSintatico(cont,"verificarStatementFor");
}

void verificarStatementWhile(int cont){
    printfSintatico(cont,"verificarStatementWhile");
}

void verificarExpressaoFinalMesmo(int cont){
    printfSintatico(cont,"verificarExpressaoFinalMesmo");
}

void verificarStatementIf(int cont){
    printfSintatico(cont,"verificarStatementIf");
}

void verificarStatementEscopo(int cont){
    printfSintatico(cont,"verificarStatementEscopo");
}



void verificarStatement(int cont){
    printfSintatico(cont,"verificarStatement");
    Token *aux = getToken();
    if(tokenIgual(aux,"if")){
        consumirToken(cont);
        verificarCondicao(cont+1);
    }else{
        erroSintatico(aux,"Condicao 'if' esperada.");
    }
}

void verificarCondicao(int cont){
    printfSintatico(cont,"verificarCondicao");
    verificarExpressao(cont+1);
    verificarCondicaoLinha(cont+1);
    
}

void verificarExpressao(int cont){
    printfSintatico(cont,"verificarExpressao");
    verificarExpressaoFinal(cont+1);
    verificarExpressaoLinha(cont+1);
}

void verificarExpressaoFinal(int cont){
    printfSintatico(cont,"verificarExpressaoFinal");
    //token == (
    Token *aux = getToken();
    if(tokenIgual(aux,"abre_parenteses")){
        consumirToken(cont);
        
        verificarCondicao(cont+1);
        aux = getToken();
        printfSintatico(cont,"verificarExpressaoFinal");
        //token == )
        if(tokenIgual(aux,"fecha_parenteses")){
            consumirToken(cont);
            return;
        }else{
            erroSintatico(aux,"Caracter inesperado encontrado. Esperado: ')'.");
        }
    }
    
    //token == identificador
    printfSintatico(cont,"verificarExpressaoFinal id");
    if(tokenIgual(aux,"identificador")){
        consumirToken(cont);
    }
}

void verificarCondicaoLinha(int cont){
    printfSintatico(cont,"verificarCondicaoLinha");
    //token == +
    Token *aux = getToken();
    if(tokenIgual(aux,"mais")){
        consumirToken(cont);
        verificarExpressao(cont+1);
        verificarCondicaoLinha(cont+1);
    }
    
    return;
}

void verificarExpressaoLinha(int cont){
    printfSintatico(cont,"verificarExpressaoLinha");
    //token == *
    Token *aux = getToken();
    if(tokenIgual(aux,"vezes")){
        
        consumirToken(cont);
        //printf("aaaaaa");
        //getchar();
        //getchar();
        verificarExpressaoFinal(cont+1);
        verificarExpressaoLinha(cont+1);
    }
    
    return;
}