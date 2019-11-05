#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/semantico.h"

int consultarTabelaIdentificadores(TabelaIdentificadores *tabela, char *identificador){
	Identificador *aux = tabela->primeira;
	while(aux != NULL){
		if(!strcmp(identificador,aux->nome)){
			return 1;
		}
		aux = aux->proxima;
	}

	return 0;
}

void printTabelaIdentificadores(TabelaIdentificadores *tabela){
	Identificador *aux = tabela->primeira;
	while(aux != NULL){
		printf("%s\t%s\t%s\t%d\t%d\t\n",aux->nome,aux->tipo,aux->valor,aux->linha,aux->coluna);
		aux = aux->proxima;
	}
}