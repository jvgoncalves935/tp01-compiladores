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

void warningsSemanticos(){
	validarVariaveisInutilizadas();
}

void validarVariaveisInutilizadas(){
	Identificador *aux = tabelaIdentificadores->primeira;
	while(aux != NULL){
		if(!strcmp("",aux->valor)){
			printf("AVISO: Variavel %s foi declarada, porem nao foi inicializada. Linha %d, Coluna %d\n",aux->nome,aux->linha,aux->coluna);
		}
		aux = aux->proxima;
	}
}

char *descobrirTipo(char *valor){
	int tamanho = strlen(valor);
	printf("%s\n",valor);
	if(tamanho > 2){
		if(validarNumero(valor[0]) && valor[1] == '.'){
			return "float";
		}
	}

	if(valor[0] == 39){
		sprintf(valor,"%c",valor[1]);
		return "char";
	}

	int i;

	if(valor[0] == '"'){
		char aux[tamanho-1];
		for(i=0;i<tamanho-2;i++){
			aux[i] = valor[i+1];
		}
		aux[i] = '\0';
		sprintf(valor,"%s",aux);
		return "string";
	}

	return "int";

}

int validarLetra(char valor){
	if((valor >= 65 && valor <= 90) || (valor >= 97 && valor <= 122)){
		return 1;
	}
	return 0;
}

int validarNumero(char valor){
	if(valor >= 48 && valor <= 57){
		return 1;
	}
	return 0;
}

