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
		printf("%s\t\t%s\t\t%s\t\t%d\t\t%d\t\n",aux->nome,aux->tipo,aux->valor,aux->linha,aux->coluna);
		aux = aux->proxima;
	}
}

void alterarTabelaIdTipo(TabelaIdentificadores *tabela, char *nome, char *tipo){
	Identificador *aux = tabela->primeira;
	while(aux != NULL){
		if(!strcmp(nome,aux->nome)){
			aux->tipo = realloc(aux->tipo,strlen(tipo)+1);
        	strcpy(aux->tipo,tipo);
			return;
		}
		aux = aux->proxima;
	}
}

void alterarTabelaIdValor(TabelaIdentificadores *tabela, char *nome, char *valor){
	Identificador *aux = tabela->primeira;
	while(aux != NULL){
		if(!strcmp(nome,aux->nome)){
			aux->valor = realloc(aux->valor,strlen(valor)+1);
        	strcpy(aux->valor,valor);
			return;
		}
		aux = aux->proxima;
	}
}

void alterarTabelaIdLinhaColuna(TabelaIdentificadores *tabela, char *nome, int linha, int coluna){
	Identificador *aux = tabela->primeira;
	while(aux != NULL){
		if(!strcmp(nome,aux->nome)){
			aux->linha = linha;
			aux->coluna = coluna;
			return;
		}
		aux = aux->proxima;
	}
}