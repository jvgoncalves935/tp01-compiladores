#include <stdio.h>
#include <stdlib.h>
#include "../headers/utils.h"
#include <string.h>
/*
char LETRA[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
char SEPARADOR[] = "S";
char COMENTARIO[] = "//";
char IDENTIFICADOR[] = "I";
char NUMERO[] = "0123456789";
char OPERADOR[] = "+*%/=<>!|&~^-?";
char NULO = '-';
*/

int TAM_ASCII = 127;
char LETRA[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
char SEPARADOR[] = " ;\n\t()[]{}.,";
char COMENTARIO[] = "//";
char IDENTIFICADOR[] = "I";
char NUMERO[] = "0123456789";
char OPERADOR[] = "+*%/=<>!|&~^-?";
char NULO = '-';
int LINHA = 1;
int COLUNA = 1;
char BUFFER[1024];

void iniciarPalavrasReservadas(char **matriz){
    matriz[0] = "auto";
    matriz[1] = "break";
    matriz[2] = "case";
    matriz[3] = "char";
    matriz[4] = "const";
    matriz[5] = "continue";
    matriz[6] = "default";
    matriz[7] = "do";
    matriz[8] = "int";
    matriz[9] = "long";
    matriz[10] = "register";
    matriz[11] = "return";
    matriz[12] = "short";
    matriz[13] = "signed";
    matriz[14] = "sizeof";
    matriz[15] = "static";
    matriz[16] = "struct";
    matriz[17] = "switch";
    matriz[18] = "typedef";
    matriz[19] = "union";
    matriz[20] = "unsigned";
    matriz[21] = "void";
    matriz[22] = "volatile";
    matriz[23] = "while";
    matriz[24] = "double";
    matriz[25] = "else";
    matriz[26] = "enum";
    matriz[27] = "extern";
    matriz[28] = "float";
    matriz[29] = "for";
    matriz[30] = "goto";
    matriz[31] = "if";
}

/*
void iniciarLetras(char *vetor){
    int i;
    for(i = 0; i < 128; i++){
        vetor[i] = '-';
    }

    for(i = 65; i <= 90; i++){
        vetor[i] = LETRA;
    }
    for(i = 97; i <= 122; i++){
        vetor[i] = LETRA;
    }
}

void iniciarNumeros(char *vetor){
    int i;

    for(i = 48; i <= 57; i++){
        vetor[i] = NUMERO;
    }
}

void iniciarOperadores(char *vetor){
    vetor[43] = OPERADOR;
    vetor[42] = OPERADOR;
    vetor[47] = OPERADOR;
    vetor[37] = OPERADOR;
    vetor[61] = OPERADOR;
    vetor[60] = OPERADOR;
    vetor[62] = OPERADOR;
    vetor[33] = OPERADOR;
    vetor[124] = OPERADOR;
    vetor[38] = OPERADOR;
    vetor[126] = OPERADOR;
    vetor[94] = OPERADOR;
    vetor[45] = OPERADOR;
    vetor[63] = OPERADOR;
}

void iniciarSeparadores(char *vetor){
    vetor[94] = SEPARADOR;
    vetor[59] = SEPARADOR;
}

void iniciarTabelaAscii(char *vetor){
    iniciarLetras(vetor);
    iniciarNumeros(vetor);
    iniciarOperadores(vetor);
    iniciarSeparadores(vetor);
}
*/

int listaVazia(Estado *f){
	if(f->numTransicoes == 0){
		return 1;
	}else{
		return 0;
	}
}

//Inicia uma célula para receber um lista.
void iniciarLista(Estado *aux){
    aux->primeira = (Transicao *) malloc(sizeof(Transicao));
    aux->primeira->proxima = NULL;
    aux->primeira->anterior = NULL;
    aux->primeira->proximoEstado = 0;
	aux->numTransicoes = 0;
    aux->final = 0;
}

//Insere valores em uma lista.
void inserirLista(Estado *f, char *transicao, int proxEstado){

	Transicao *aux;
	aux = (Transicao *) malloc(sizeof(Transicao));

    aux->conjunto = malloc(strlen(transicao)*(sizeof(char)));
	strcpy(aux->conjunto,transicao);

	aux->proxima = NULL;
    aux->anterior = NULL;
    aux->proximoEstado = proxEstado;

	if(listaVazia(f)){
		f->primeira = aux;
        f->ultima = aux;
		f->numTransicoes++;
	}else{
        aux->anterior = f->ultima;
        f->ultima->proxima = aux;
        f->ultima = aux;
		f->numTransicoes++;
	}
}

int listaVaziaToken(ListaToken *f){
	if(f->numTokens == 0){
		return 1;
	}else{
		return 0;
	}
}

//Inicia uma célula para receber um lista.
void iniciarListaToken(ListaToken *aux){
    aux->primeira = (Token *) malloc(sizeof(Token));
    aux->primeira->proxima = NULL;
    aux->primeira->anterior = NULL;
    aux->primeira->linha = 0;
    aux->primeira->coluna = 0;
	aux->numTokens = 0;
}

//Insere valores em uma lista.
void inserirListaToken(ListaToken *f, char *valor, char *valorBruto, int _linha, int _coluna){
	Token *aux;
	aux = (Token *) malloc(sizeof(Token));

    aux->valor = malloc(strlen(valor)*(sizeof(char)));
	strcpy(aux->valor,valor);

    aux->valorBruto = malloc(strlen(valorBruto)*(sizeof(char)));
	strcpy(aux->valorBruto,valorBruto);

	aux->proxima = NULL;
    aux->anterior = NULL;
    aux->linha = _linha;
    aux->coluna = _coluna;

	if(listaVaziaToken(f)){
		f->primeira = aux;
        f->ultima = aux;
		f->numTokens++;
	}else{
        aux->anterior = f->ultima;
        f->ultima->proxima = aux;
        f->ultima = aux;
		f->numTokens++;
	}
}

void setEstadoFinal(MaquinaEstados *maquinaEstados, int estado){
    maquinaEstados->estados[estado].final = 1;
}

/*
Transicao *ultimoLista(Transicao *primeiro){
    Transicao *aux = primeiro;
    if(aux == NULL){
        return NULL;
    }
    while(true){
        if(aux->proxima == NULL){
            return aux;
        }
        aux = aux->proxima;
    }
}
*/