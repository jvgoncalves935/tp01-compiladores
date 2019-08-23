#include <stdio.h>
#include "../headers/utils.h"

int TAM_ASCII = 127;
char LETRA = 'L';
char SEPARADOR = 'S';
char COMENTARIO = 'C';
char IDENTIFICADOR = 'I';
char NUMERO = 'N';
char OPERADOR = 'O';
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

