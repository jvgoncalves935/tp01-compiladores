#include <stdio.h>
#include <stdlib.h>
#include "../headers/utils.h"

int main(){
    int i;
    
    char tabela_ascii[TAM_ASCII];
    //char comentario = '//';
    //char literal = ''','"';
    

    char **palavras_reservadas = malloc(32*(sizeof(char *)));
    for(i=0;i<28;i++){
        palavras_reservadas[i] = malloc(15*sizeof(char));
    }

    iniciarLetras(tabela_ascii);
    iniciarNumeros(tabela_ascii);

    for(i=0;i<TAM_ASCII;i++){
        printf("%c\n",tabela_ascii[i]);
    }


    return 0;
}