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

    verificarListaDiretivas(0);
    verificarLinguagem(0);

    if(!ERRO_SINTATICO){
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
    if(!FLAG_SINTATICO || IGNORAR_TOKEN){
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
    if(!FLAG_EXIBIR_ARVORE){
        return;
    }

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
    ERRO_SINTATICO = 1;
    if(!FLAG_SINTATICO){
        return;
    }
    printf("Analise Sintatica: ERRO. %s Linha %d, Coluna %d.\nToken encontrado: %s\n",erro,token->linha,token->coluna,token->valor);
    //exit(0);
    
    IGNORAR_TOKEN = 1;
    proximoPontoVirgula();
}

void proximoPontoVirgula(){
    Token *aux = LISTATOKEN->primeira;
    while(strcmp(LISTATOKEN->primeira->valor,"ponto_virgula") != 0){
        if(LISTATOKEN->primeira == NULL){
            printf("LISTATOKEN vazia.\n");
            exit(0);
        }
        aux = LISTATOKEN->primeira;
        LISTATOKEN->primeira = LISTATOKEN->primeira->proxima;

        free(aux->valor);
        free(aux->valorBruto);
        free(aux);
        //LISTATOKEN->primeira = LISTATOKEN->primeira->proxima;
    }
}

int verificarListaDiretivas(int cont){
    printfSintatico(cont,"verificarListaDiretivas");
    Token *aux = LISTATOKEN->primeira;
    if(aux != NULL){
        if(tokenIgual(aux,"diretiva")){
            consumirToken(0);
            verificarListaDiretivas(cont+1);
        }
    }else{
        erroSintatico(aux,"Final do arquivo inesperado em declaracoes de diretivas.");
    }
    return 0;
}

int verificarLinguagem(int cont){
    while(LISTATOKEN->primeira != NULL){
        if(!strcmp(LISTATOKEN->primeira->valor,"negacao")){
            consumirToken(0);
        }else{
            printfSintatico(cont,"verificarLinguagem");
            verificarFuncao(cont+1);
        }
    }
    return 0;
}

int verificarFuncao(int cont){
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
    return 0;
}

int verificarTipo(int cont){
    printfSintatico(cont,"verificarTipo");
    Token *aux = getToken();
    if(tokenIgual(aux,"int") || tokenIgual(aux,"float") || tokenIgual(aux,"char") || tokenIgual(aux,"double") || tokenIgual(aux,"void")){
        consumirToken(cont); return 0;
    }
    return 0;
    //erroSintatico(aux,"Tipo invalido para funcao.");
    
}

int verificarListaArg(int cont){
    printfSintatico(cont,"verificarListaArg");
    verificarArg(cont+1);
    if(strcmp(LISTATOKEN->primeira->valor,"virgula")){
        return 0;
    }

    Token *aux = getToken();
    if(tokenIgual(aux,"virgula")){
        consumirToken(cont);
        verificarListaArg(cont+1);
        return 0;
    }
    /*
    else{
        erroSintatico(aux,"Expressao invalida em parametro de funcao (era esperado uma virgula).");
    }
    */

    

    return 0;
}

int verificarArg(int cont){
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
    return 0;
}

int verificarDeclaracao(int cont){
    printfSintatico(cont,"verificarDeclaracao");
    verificarTipo(cont+1);
    verificarListaIdentificadores(cont+1);
    return 0;
}

int verificarListaIdentificadores(int cont){
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
    return 0;
}

int verificarStatement(int cont){
    printfSintatico(cont,"verificarStatement");
    Token *aux;
    aux = getToken();

    do{
        if(tokenIgual(aux,"for")){
            verificarStatementFor(cont+1);
            return 1;
        }
        if(tokenIgual(aux,"while")){
            verificarStatementWhile(cont+1);
            return 1;
        }
        if(tokenIgual(aux,"identificador") && tokenDiferente(aux->proxima,"abre_parenteses")){
            verificarExpressao(cont+1);
            return 1;
        }
        if(tokenIgual(aux,"identificador") && tokenIgual(aux->proxima,"abre_parenteses")){
            verificarChamadaFuncao(cont+1);
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
            //consumirToken(cont);
            verificarDeclaracao(cont+1);
            return 1;
        }
        if(tokenIgual(aux,"do")){
            verificarStatementDoWhile(cont+1);
            return 1;
        }
        if(tokenIgual(aux,"return")){
            consumirToken(cont);

            verificarStatementReturn(cont+1);

            aux = getToken();
            if(tokenIgual(aux,"ponto_virgula")){
                consumirToken(cont);
                return 1;
            }else{
                erroSintatico(aux,"Esperado ponto_virgula apos 'return'.");
                return 0;
            }   
        }
        if(tokenIgual(aux,"break")){
            consumirToken(cont);
            aux = getToken();
            if(tokenIgual(aux,"ponto_virgula")){
                consumirToken(cont);
                return 1;
            }else{
                erroSintatico(aux,"Esperado ponto_virgula apos 'break'.");
                return 0;
            }   
        }
        if(tokenIgual(aux,"switch")){
            verificarSwitch01(cont+1);
            return 1;
        }

        if(tokenIgual(aux,"ponto_virgula")){
            if(IGNORAR_TOKEN){
                IGNORAR_TOKEN = 0;
                continue;
            }
            consumirToken(cont);
            return 1;
        }
    }while(IGNORAR_TOKEN);
    return 0;

    //Erro no statement
    //erroSintatico(aux,"Expressao invalida em statement.");
}

int verificarStatementFor(int cont){
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
    return 0;
}

int verificarStatementWhile(int cont){
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
    return 0;
}

int verificarStatementReturn(int cont){
    printfSintatico(cont,"verificarStatementReturn");
    Token *aux = getToken();
    if(tokenIgual(aux,"identificador") || tokenIgual(aux,"numero") || tokenIgual(aux,"aspas_simples") || tokenIgual(aux,"aspas_duplas")){
        consumirToken(cont);
    }
    return 0;
}

int verificarExpressao(int cont){
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
        return 0;
    }

    verificarValorR(cont+1);
    return 0;
}

int verificarExpressao02(int cont){
    printfSintatico(cont,"verificarExpressao02");
    Token *aux = getToken();
    if(tokenIgual(aux,"igual")){
        consumirToken(cont);
        verificarExpressao(cont+1);
        return 0;
    }

    if(isComparacao(aux)){
        verificarComparacao(cont+1);
        verificarExpressao(cont+1);
        return 0;
    }

    if(isAritmetica(aux)){
        verificarAritmetica(cont+1);
        verificarExpressao(cont+1);
        return 0;
    }

    if(isAritmeticaOperadorDuplicado(aux)){
        verificarAritmeticaOperadorDuplicado(cont+1);
        return 0;
    }

    if(isAritmeticaOperadorIgualComposto(aux)){
        verificarAritmeticaOperadorIgualComposto(cont+1);
        verificarExpressao(cont+1);
        return 0;
    }
    return 0;
    
}

int verificarStatementIf(int cont){
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
    return 0;
}

int verificarStatementEscopo(int cont){
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
    return 0;

}


int verificarExpressaoOpcional(int cont){
    printfSintatico(cont,"verificarExpressaoOpcional");
    verificarExpressao(cont+1);
    return 0;
}

int verificarParteElse(int cont){
    printfSintatico(cont,"verificarParteElse");
    Token *aux = getToken();
    if(tokenIgual(aux,"else")){
        consumirToken(cont);
        verificarStatement(cont+1);
    }
    return 0;
}

int verificarListaStatement(int cont){
    printfSintatico(cont,"verificarListaStatement");
    verificarStatement(cont+1);
    verificarListaStatementLinha(cont+1);
    return 0;
}

int verificarListaStatementLinha(int cont){
    printfSintatico(cont,"verificarListaStatementLinha");
    int res = verificarStatement(cont+1);
    if(res == 1){
        verificarListaStatementLinha(cont+1);
    }
    return 0;
}

int verificarValorR(int cont){
    printfSintatico(cont,"verificarValorR");
    Token *aux = getToken();
    if(isComparacao(aux)){
        verificarComparacao(cont+1);
        verificarMagnitude(cont+1);
        verificarValorRLinha(cont+1); 
    }else{
        verificarMagnitude(cont+1);
        return 0;
    }
    return 0;

}

int verificarValorRLinha(int cont){
    printfSintatico(cont,"verificarRLinha");
    Token *aux = getToken();
    if(isComparacao(aux)){
        verificarComparacao(cont+1);
        verificarMagnitude(cont+1);
        verificarValorRLinha(cont+1);
    }
    return 0;
}

int verificarComparacao(int cont){
    printfSintatico(cont,"verificarComparacao");
    Token *aux = getToken();
    if(isComparacao(aux)){
        consumirToken(cont);
    }else{
        erroSintatico(aux,"Comparador invalido encontrado em expressao.");
    }
    return 0;
}

int verificarMagnitude(int cont){
    printfSintatico(cont,"verificarMagnitude");
    verificarTermo(cont+1);
    verificarMagnitudeLinha(cont+1);
    return 0;
}

int verificarMagnitudeLinha(int cont){
    printfSintatico(cont,"verificarMagnitudeLinha");
    Token *aux = getToken();
    if(tokenIgual(aux,"mais")){
        consumirToken(cont);
        verificarTermo(cont+1);
        verificarMagnitudeLinha(cont+1);
        return 0;
    }

    aux = getToken();
    if(tokenIgual(aux,"menos")){
        consumirToken(cont);
        verificarTermo(cont+1);
        verificarMagnitudeLinha(cont+1);
        return 0;
    }
    return 0;
}

int verificarTermo(int cont){
    printfSintatico(cont,"verificarTermo");
    verificarFator(cont+1);
    verificarTermoLinha(cont+1);
    return 0;
}

int verificarTermoLinha(int cont){
    printfSintatico(cont,"verificarTermoLinha");
    Token *aux = getToken();
    if(tokenIgual(aux,"vezes")){
        consumirToken(cont);
        verificarFator(cont+1);
        verificarTermoLinha(cont+1);
        return 0;
    }

    aux = getToken();
    if(tokenIgual(aux,"barra")){
        consumirToken(cont);
        verificarFator(cont+1);
        verificarTermoLinha(cont+1);
        return 0;
    }
    return 0;

}

int verificarFator(int cont){
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
        return 0;
    }

    if(tokenIgual(aux,"mais")){
        consumirToken(cont);
        verificarFator(cont+1);
        return 0;
    }

    if(tokenIgual(aux,"identificador")){
        consumirToken(cont);
        return 0;
    }

    if(tokenIgual(aux,"numero")){
        consumirToken(cont);
        return 0;
    }

    if(tokenIgual(aux,"aspas_simples")){
        consumirToken(cont);
        return 0;
    }

    if(tokenIgual(aux,"aspas_duplas")){
        consumirToken(cont);
        return 0;
    }
    return 0;

    //erroSintatico(aux,"Caracter invalido encontrado em fator de expressao.");
    
}

int verificarAritmetica(int cont){
    printfSintatico(cont,"verificarAritmetica");
    Token *aux = getToken();
    if(tokenIgual(aux,"mais") || tokenIgual(aux,"menos") || tokenIgual(aux,"vezes") || tokenIgual(aux,"barra")){
        consumirToken(cont);
    }
    return 0;
}

int verificarAritmeticaOperadorDuplicado(int cont){
    printfSintatico(cont,"verificarAritmeticaOperadorDuplicado");
    Token *aux = getToken();
    if(tokenIgual(aux,"mais_mais") || tokenIgual(aux,"menos_menos") || tokenIgual(aux,"vezes_vezes")){
        consumirToken(cont);
    }
    return 0;
}

int verificarAritmeticaOperadorIgualComposto(int cont){
    printfSintatico(cont,"verificarAritmeticaOperadorIgualComposto");
    Token *aux = getToken();
    if(tokenIgual(aux,"mais_igual") || tokenIgual(aux,"menos_igual") || tokenIgual(aux,"vezes_igual") || tokenIgual(aux,"barra_igual")){
        consumirToken(cont);
    }
    return 0;
}

int verificarStatementDoWhile(int cont){
    printfSintatico(cont,"verificarStatementDoWhile");
    Token *aux = getToken();
    if(tokenIgual(aux,"do")){
        consumirToken(cont);
        verificarStatementEscopo(cont+1);

        aux = getToken();
        if(tokenIgual(aux,"while")){
            consumirToken(cont);
            aux = getToken();

            if(tokenIgual(aux,"abre_parenteses")){
                consumirToken(cont);
                verificarExpressao(cont+1);

                aux = getToken();
                if(tokenIgual(aux,"fecha_parenteses")){
                    consumirToken(cont);
                }else{
                    erroSintatico(aux,"Esperado fecha_parenteses apos while de uma instrucao 'do'.");
                }
            }else{
                erroSintatico(aux,"Esperado abre_parenteses apos while de uma instrucao 'do'.");
            }

        }
    }
    return 0;
}

int verificarSwitch01(int cont){
    printfSintatico(cont,"verificarSwitch01");
    Token *aux = getToken();
    if(tokenIgual(aux,"switch")){
        consumirToken(cont);
    }

    aux = getToken();
    if(tokenIgual(aux,"abre_parenteses")){
        consumirToken(cont);
    }else{
        erroSintatico(aux,"Esperado abre_parenteses dentro do parametro de uma instrucao 'switch'.");
    }

    verificarSwitch02(cont+1);

    aux = getToken();
    if(tokenIgual(aux,"fecha_parenteses")){
        consumirToken(cont);
    }else{
        erroSintatico(aux,"Esperado fecha_parenteses dentro do parametro de uma instrucao 'switch'.");
    }

    aux = getToken();
    if(tokenIgual(aux,"abre_chaves")){
        consumirToken(cont);
    }else{
        erroSintatico(aux,"Esperado abre_chaves apos parametro de uma instrucao 'switch'.");
    }

    verificarListaCase(cont+1);

    aux = getToken();
    if(tokenIgual(aux,"fecha_chaves")){
        consumirToken(cont);
    }else{
        erroSintatico(aux,"Esperado fecha_chaves apos instrucao 'switch'.");
    }
    return 0;

}

int verificarSwitch02(int cont){
    printfSintatico(cont,"verificarSwitch02");
    Token *aux = getToken();
    if(tokenIgual(aux,"numero") || tokenIgual(aux,"identificador")  || tokenIgual(aux,"aspas_simples")  || tokenIgual(aux,"aspas_duplas")){
        consumirToken(cont);
        return 0;
    }

    erroSintatico(aux,"Tipo de parametro invalido em instrucao 'switch'.");
    return 1;
}

int verificarListaCase(int cont){
    printfSintatico(cont,"verificarListaCase");
    Token *aux = getToken();
    if(tokenIgual(aux,"case")){
        consumirToken(cont);

        verificarSwitch02(cont+1);

        aux = getToken();
        if(tokenIgual(aux,"dois_pontos")){
            consumirToken(cont);
            
            verificarListaStatement(cont+1);
            verificarListaCaseLinha(cont+1);
            return 0;
        }
    }

    erroSintatico(aux,"Erro na primeira em instrucao 'case'.");
    return 1;
}

int verificarListaCaseLinha(int cont){
    printfSintatico(cont,"verificarListaCaseLinha");
    Token *aux = getToken();
    if(tokenIgual(aux,"case")){
        consumirToken(cont);

        verificarSwitch02(cont+1);

        aux = getToken();
        if(tokenIgual(aux,"dois_pontos")){
            consumirToken(cont);
            
            verificarListaStatement(cont+1);
            verificarListaCaseLinha(cont+1);
            return 0;
        }
    }

    if(tokenIgual(aux,"default")){
        consumirToken(cont);
        aux = getToken();
        if(tokenIgual(aux,"dois_pontos")){
            consumirToken(cont);

            verificarListaStatement(cont+1);
            return 0;
        }
    }
    return 0;
}

int verificarChamadaFuncao(int cont){
    printfSintatico(cont,"verificarChamadaFuncao");
    Token *aux = getToken();

    if(tokenIgual(aux,"identificador")){
        consumirToken(cont);

        aux = getToken();
        if(tokenIgual(aux,"abre_parenteses")){
            consumirToken(cont);
            aux = getToken();
            if(tokenDiferente(aux,"fecha_parenteses")){
                verificarListaArgChamadaFuncao(cont+1);
            }
            
            aux = getToken();
            if(tokenIgual(aux,"fecha_parenteses")){
                consumirToken(cont);
                
                aux = getToken();
                if(tokenIgual(aux,"ponto_virgula")){
                    consumirToken(cont);
                    return 0;
                }
            }else{
                erroSintatico(aux,"Esperado fecha_parenteses apos chamada de funcao.");
            }
        }
    }
    return 0;
}

int verificarListaArgChamadaFuncao(int cont){
    printfSintatico(cont,"verificarListaArgChamadaFuncao");
    
    verificarSwitch02(cont+1);
    verificarListaArgChamadaFuncaoLinha(cont+1);
    return 0;
}

int verificarListaArgChamadaFuncaoLinha(int cont){
    printfSintatico(cont,"verificarListaArgChamadaFuncaoLinha");
    Token *aux = getToken();
    if(tokenIgual(aux,"virgula")){
        consumirToken(cont);
        
        verificarSwitch02(cont+1);
        verificarListaArgChamadaFuncaoLinha(cont+1);
    }
    return 0;
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

int isAritmeticaOperadorDuplicado(Token *aux){
    if(tokenIgual(aux,"mais_mais") || tokenIgual(aux,"menos_menos") || tokenIgual(aux,"vezes_vezes")){
        return 1;
    }
    return 0;
}

int isAritmeticaOperadorIgualComposto(Token *aux){
    if(tokenIgual(aux,"mais_igual") || tokenIgual(aux,"menos_igual") || tokenIgual(aux,"vezes_igual") || tokenIgual(aux,"barra_igual")){
        return 1;
    }
    return 0;
}