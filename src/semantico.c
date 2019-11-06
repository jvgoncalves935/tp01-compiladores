#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/semantico.h"

TabelaIdentificadores *tabelaIdentificadores;

int consultarTabelaIdentificadores(char *identificador){
	Identificador *aux = tabelaIdentificadores->primeira;
	while(aux != NULL){
		if(!strcmp(identificador,aux->nome)){
			return 1;
		}
		aux = aux->proxima;
	}

	return 0;
}

void printTabelaIdentificadores(){
	Identificador *aux = tabelaIdentificadores->primeira;
	while(aux != NULL){
		printf("%s\t\t%s\t\t%s\t\t%d\t\t%d\t\n",aux->nome,aux->tipo,aux->valor,aux->linha,aux->coluna);
		aux = aux->proxima;
	}
}

void alterarTabelaIdTipo(char *nome, char *tipo){
	Identificador *aux = tabelaIdentificadores->primeira;
	while(aux != NULL){
		if(!strcmp(nome,aux->nome)){
			aux->tipo = realloc(aux->tipo,strlen(tipo)+1);
        	strcpy(aux->tipo,tipo);
			return;
		}
		aux = aux->proxima;
	}
}

void alterarTabelaIdValor(char *nome, char *valor){
	Identificador *aux = tabelaIdentificadores->primeira;
	while(aux != NULL){
		if(!strcmp(nome,aux->nome)){
			aux->valor = realloc(aux->valor,strlen(valor)+1);
        	strcpy(aux->valor,valor);
			return;
		}
		aux = aux->proxima;
	}
}

void alterarTabelaIdLinhaColuna(char *nome, int linha, int coluna){
	Identificador *aux = tabelaIdentificadores->primeira;
	while(aux != NULL){
		if(!strcmp(nome,aux->nome)){
			aux->linha = linha;
			aux->coluna = coluna;
			return;
		}
		aux = aux->proxima;
	}
}

Identificador *tabelaLinhaColunaVariavel(char *nome){
	Identificador *aux = tabelaIdentificadores->primeira;
	while(aux != NULL){
		if(!strcmp(nome,aux->nome)){
			return aux;
		}
		aux = aux->proxima;
	}
	return aux;

}