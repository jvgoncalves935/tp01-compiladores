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
    printf("Analise Sintatica: ERRO. %s Linha %d, Coluna %d.\nToken encontrado: %s\n",erro,token->linha,token->coluna,token->valor);
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
    }
    /*
    else{
        erroSintatico(aux,"Expressao invalida em declaracao de funcao (era esperado um identificador).");
    }
    */

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
    /*
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
    */

    verificarStatementEscopo(cont+1);
    
    //verificarStatement(cont+1);
}

void verificarTipo(int cont){
    printfSintatico(cont,"verificarTipo");
    Token *aux = getToken();
    if(tokenIgual(aux,"int") || tokenIgual(aux,"float") || tokenIgual(aux,"char") || tokenIgual(aux,"double") || tokenIgual(aux,"void")){
        consumirToken(cont); return;
    }
    //erroSintatico(aux,"Tipo invalido para funcao.");
    
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
        verificarListaArg(cont+1);
        return;
    }
    /*
    else{
        erroSintatico(aux,"Expressao invalida em parametro de funcao (era esperado uma virgula).");
    }
    */

    


}

void verificarArg(int cont){
    printfSintatico(cont,"verificarArg");
    verificarTipo(cont+1);

    Token *aux = getToken();
    if(tokenIgual(aux,"identificador")){
        consumirToken(cont);
    }
    /*
    else{
        erroSintatico(aux,"Expressao invalida em parametro de funcao (era esperado um identificador).");
    }
    */
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

int verificarStatement(int cont){
    printfSintatico(cont,"verificarStatement");
    Token *aux = getToken();

    if(tokenIgual(aux,"for")){
        verificarStatementFor(cont+1);
        return 1;
    }
    if(tokenIgual(aux,"while")){
        verificarStatementWhile(cont+1);
        return 1;
    }
    if(tokenIgual(aux,"identificador")){
        verificarExpressao(cont+1);
        return 1;
    }
    if(tokenIgual(aux,"if")){
        verificarStatementIf(cont+1);
        return 1;
    }
    if(tokenIgual(aux,"abre_chaves")){
        verificarStatementEscopo(cont+1);
        return 1;
    }
    if(isTipoDeclaracao(aux)){
        consumirToken(cont);
        verificarDeclaracao(cont+1);
        return 1;
    }
    if(tokenIgual(aux,"ponto_virgula")){
        consumirToken(cont);
        return 1;
    }

    return 0;

    //Erro no statement
    //erroSintatico(aux,"Expressao invalida em statement.");
}

void verificarStatementFor(int cont){
    printfSintatico(cont,"verificarStatementFor");
    Token *aux = getToken();
    if(tokenIgual(aux,"for")){
        consumirToken(cont);
    }

    aux = getToken();
    if(tokenIgual(aux,"abre_parenteses")){
        consumirToken(cont);
    }else{
        erroSintatico(aux,"Caracter invalido em declaracao for (era esperado um abre_parenteses).");
    }

    verificarExpressao(cont+1);

    aux = getToken();
    if(tokenIgual(aux,"ponto_virgula")){
        consumirToken(cont);
    }else{
        erroSintatico(aux,"Caracter invalido em declaracao for (era esperado um ponto_virgula apos o primeiro parametro).");
    }

    verificarExpressaoOpcional(cont+1);

    aux = getToken();
    if(tokenIgual(aux,"ponto_virgula")){
        consumirToken(cont);
    }else{
        erroSintatico(aux,"Caracter invalido em declaracao for (era esperado um ponto_virgula apos o segundo parametro).");
    }

    verificarExpressaoOpcional(cont+1);

    aux = getToken();
    if(tokenIgual(aux,"fecha_parenteses")){
        consumirToken(cont);
    }else{
        erroSintatico(aux,"Caracter invalido em declaracao for (era esperado um fecha_parenteses).");
    }

    verificarStatement(cont+1);
}

void verificarStatementWhile(int cont){
    printfSintatico(cont,"verificarStatementWhile");
    Token *aux = getToken();
    if(tokenIgual(aux,"while")){
        consumirToken(cont);
    }

    aux = getToken();
    if(tokenIgual(aux,"abre_parenteses")){
        consumirToken(cont);
    }else{
        erroSintatico(aux,"Caracter invalido em declaracao while (era esperado um abre_parenteses).");
    }

    verificarExpressao(cont+1);

    aux = getToken();
    if(tokenIgual(aux,"fecha_parenteses")){
        consumirToken(cont);
    }else{
        erroSintatico(aux,"Caracter invalido em declaracao while (era esperado um fecha_parenteses).");
    }

    verificarStatement(cont+1);
}

void verificarExpressao(int cont){
    printfSintatico(cont,"verificarExpressao");
    Token *aux = getToken();
    if(tokenIgual(aux,"identificador")){
        consumirToken(cont);
        /*
        aux = getToken();
        if(tokenIgual(aux,"igual")){
            consumirToken(cont);
        }else{
            erroSintatico(aux,"Caracter invalido em expressao (era esperado um igual).");
        }
        verificarExpressao(cont+1);
        */
        verificarExpressao02(cont+1);
        return;
    }

    verificarValorR(cont+1);
}

void verificarExpressao02(int cont){
    printfSintatico(cont,"verificarExpressao02");
    Token *aux = getToken();
    if(tokenIgual(aux,"igual")){
        consumirToken(cont);
        verificarExpressao(cont+1);
        return;
    }

    if(isComparacao(aux)){
        verificarComparacao(cont+1);
        verificarExpressao(cont+1);
    }

    if(isAritmetica(aux)){
        verificarAritmetica(cont+1);
        verificarExpressao(cont+1);
    }
    
}

void verificarStatementIf(int cont){
    printfSintatico(cont,"verificarStatementIf");
    Token *aux = getToken();
    if(tokenIgual(aux,"if")){
        consumirToken(cont);
    }

    aux = getToken();
    if(tokenIgual(aux,"abre_parenteses")){
        consumirToken(cont);
    }else{
        erroSintatico(aux,"Caracter invalido em declaracao if (era esperado um abre_parenteses).");
    }

    verificarExpressao(cont+1);

    aux = getToken();
    if(tokenIgual(aux,"fecha_parenteses")){
        consumirToken(cont);
    }else{
        erroSintatico(aux,"Caracter invalido em declaracao if (era esperado um fecha_parenteses).");
    }

    verificarStatement(cont+1);

    verificarParteElse(cont+1);
}

void verificarStatementEscopo(int cont){
    printfSintatico(cont,"verificarStatementEscopo");
    Token *aux = getToken();
    if(tokenIgual(aux,"abre_chaves")){
        consumirToken(cont);
    }

    verificarListaStatement(cont+1);

    aux = getToken();
    if(tokenIgual(aux,"fecha_chaves")){
        consumirToken(cont);
    }else{
        erroSintatico(aux,"Caracter invalido em statement (era esperado um fecha_chaves).");
    }

}


void verificarExpressaoOpcional(int cont){
    printfSintatico(cont,"verificarExpressaoOpcional");
    verificarExpressao(cont+1);
}

void verificarParteElse(int cont){
    printfSintatico(cont,"verificarParteElse");
    Token *aux = getToken();
    if(tokenIgual(aux,"else")){
        consumirToken(cont);
        verificarStatement(cont+1);
    }
}

void verificarListaStatement(int cont){
    printfSintatico(cont,"verificarListaStatement");
    verificarStatement(cont+1);
    verificarListaStatementLinha(cont+1);
}

void verificarListaStatementLinha(int cont){
    printfSintatico(cont,"verificarListaStatementLinha");
    int res = verificarStatement(cont+1);
    if(res == 1){
        verificarListaStatementLinha(cont+1);
    }
}

void verificarValorR(int cont){
    printfSintatico(cont,"verificarValorR");
    Token *aux = getToken();
    if(isComparacao(aux)){
        verificarComparacao(cont+1);
        verificarMagnitude(cont+1);
        verificarValorRLinha(cont+1); 
    }else{
        verificarMagnitude(cont+1);
        return;
    }

}

void verificarValorRLinha(int cont){
    printfSintatico(cont,"verificarRLinha");
    Token *aux = getToken();
    if(isComparacao(aux)){
        verificarComparacao(cont+1);
        verificarMagnitude(cont+1);
        verificarValorRLinha(cont+1);
    }
}

void verificarComparacao(int cont){
    printfSintatico(cont,"verificarComparacao");
    Token *aux = getToken();
    if(isComparacao(aux)){
        consumirToken(cont);
    }else{
        erroSintatico(aux,"Comparador invalido encontrado em expressao.");
    }
}

void verificarMagnitude(int cont){
    printfSintatico(cont,"verificarMagnitude");
    verificarTermo(cont+1);
    verificarMagnitudeLinha(cont+1);
}

void verificarMagnitudeLinha(int cont){
    printfSintatico(cont,"verificarMagnitudeLinha");
    Token *aux = getToken();
    if(tokenIgual(aux,"mais")){
        consumirToken(cont);
        verificarTermo(cont+1);
        verificarMagnitudeLinha(cont+1);
        return;
    }

    aux = getToken();
    if(tokenIgual(aux,"menos")){
        consumirToken(cont);
        verificarTermo(cont+1);
        verificarMagnitudeLinha(cont+1);
        return;
    }
}

void verificarTermo(int cont){
    printfSintatico(cont,"verificarTermo");
    verificarFator(cont+1);
    verificarTermoLinha(cont+1);
}

void verificarTermoLinha(int cont){
    printfSintatico(cont,"verificarTermoLinha");
    Token *aux = getToken();
    if(tokenIgual(aux,"vezes")){
        consumirToken(cont);
        verificarFator(cont+1);
        verificarTermoLinha(cont+1);
        return;
    }

    aux = getToken();
    if(tokenIgual(aux,"barra")){
        consumirToken(cont);
        verificarFator(cont+1);
        verificarTermoLinha(cont+1);
        return;
    }

}

void verificarFator(int cont){
    printfSintatico(cont,"verificarFator");
    Token *aux = getToken();
    if(tokenIgual(aux,"abre_parenteses")){
        consumirToken(cont);
        verificarExpressao(cont+1);
        aux = getToken();
        if(tokenIgual(aux,"fecha_parenteses")){
            consumirToken(cont);
        }else{
            erroSintatico(aux,"Caracter invalido encontrado apos expressao (era esperado um fecha_parenteses).");
        }
        return;
    }

    if(tokenIgual(aux,"mais")){
        consumirToken(cont);
        verificarFator(cont+1);
        return;
    }

    if(tokenIgual(aux,"identificador")){
        consumirToken(cont);
        return;
    }

    if(tokenIgual(aux,"numero")){
        consumirToken(cont);
        return;
    }

    //erroSintatico(aux,"Caracter invalido encontrado em fator de expressao.");
    
}

void verificarAritmetica(int cont){
    printfSintatico(cont,"verificarAritmetica");
    Token *aux = getToken();
    if(tokenIgual(aux,"mais") || tokenIgual(aux,"menos") || tokenIgual(aux,"vezes") || tokenIgual(aux,"barra")){
        consumirToken(cont);
    }
}

int isComparacao(Token *aux){
    if(tokenIgual(aux,"igual_igual") || tokenIgual(aux,"menor") || tokenIgual(aux,"maior") || tokenIgual(aux,"menor_igual") || tokenIgual(aux,"maior_igual") || tokenIgual(aux,"diferente")){
        return 1;
    }
    return 0;
}

int isFator(Token *aux){
    if(tokenIgual(aux,"abre_parenteses") || tokenIgual(aux,"menos") || tokenIgual(aux,"mais") || tokenIgual(aux,"identificador") || tokenIgual(aux,"numero")){
        return 1;
    }
    return 0;
}

int isTipoDeclaracao(Token *aux){
    //Token *aux = getToken();
    if(tokenIgual(aux,"int") || tokenIgual(aux,"float") || tokenIgual(aux,"char") || tokenIgual(aux,"double") || tokenIgual(aux,"void")){
        return 1;
    }
    return 0;
    
}

int isAritmetica(Token *aux){
    //Token *aux = getToken();
    if(tokenIgual(aux,"mais") || tokenIgual(aux,"menos") || tokenIgual(aux,"vezes") || tokenIgual(aux,"barra")){
        return 1;
    }
    return 0;
}