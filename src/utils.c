#include <stdio.h>
#include "../headers/utils.h"
#include "../headers/automato.h"

int TAM_ASCII = 127;
char LETRA[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
char SEPARADOR[] = 'S';
char COMENTARIO[] = "//";
char IDENTIFICADOR[] = 'I';
char NUMERO[] = "0123456789";
char OPERADOR[] = "+*%/=<>!|&~^-?";
char NULO = '-';

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
	if(f->tamanho == 0){
		return 1;
	}else{
		return 0;
	}
}

//Inicia uma célula para receber um lista.
void iniciarLista(Estado *aux){
    aux->primeira = (Transicao *) malloc(sizeof(Transicao));
    aux->primeira->proxima = NULL;
    aux->primeira->ultima = NULL;
	aux->tamanho = 0;
}

//Insere valores em uma lista.
void inserirLista(Estado *f, char *transicao){

	Transicao *aux;
	aux = (Transicao *) malloc(sizeof(Transicao));

	aux->conjunto = transicao;
	aux->proxima = NULL;
    aux->anterior = NULL;

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