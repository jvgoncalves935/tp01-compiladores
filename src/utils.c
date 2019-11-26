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
char SEPARADOR[] = " ;\n\r\t()[]{}.,:";
char COMENTARIO[] = "//";
char IDENTIFICADOR[] = "I";
char NUMERO[] = "0123456789";
char OPERADOR[] = "+*%/=<>!|&~^-?";
char NULO = '-';
int LINHA = 1;
int COLUNA = 1;
char BUFFER[1024];
int NUM_ESTADOS = 26;
ListaToken *LISTATOKEN;
int FLAG_SINTATICO = 1;
int FLAG_EXIBIR_ARVORE = 0;
int IGNORAR_TOKEN = 0;
int ERRO_SINTATICO = 0;
int ERRO_SEMANTICO = 0;
int NUM_REGISTRADORES = 0;

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

int listaVazia(Estado *f){
	if(f->numTransicoes == 0){
		return 1;
	}else{
		return 0;
	}
}

//Inicia uma celula para receber um lista.
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

    aux->conjunto = malloc((strlen(transicao)+1)*(sizeof(char)));
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

//Inicia uma celula para receber um lista.
void iniciarListaToken(ListaToken *aux){
    aux->primeira = malloc(sizeof(Token));
    aux->primeira->proxima = NULL;
    aux->primeira->anterior = NULL;
    aux->primeira->linha = 0;
    aux->primeira->coluna = 0;
	aux->numTokens = 0;
}

//Insere valores em uma lista.
void inserirListaToken(ListaToken *f, char *valor, char *valorBruto, int _linha, int _coluna){
	Token *aux;
	aux = malloc(1*sizeof(Token));

    //printf("%ld -- %d %d\n",strlen(valor),LINHA,COLUNA);
    aux->valor = malloc((strlen(valor)+1)*(sizeof(char)));
    
	strcpy(aux->valor,valor);

    aux->valorBruto = malloc((strlen(valorBruto)+1)*(sizeof(char)));
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

int tabelaVaziaIdentificadores(TabelaIdentificadores *f){
	if(f->numIdentificadores == 0){
		return 1;
	}else{
		return 0;
	}
}

//Inicia uma celula para receber um lista.
void iniciarTabelaIdentificadores(TabelaIdentificadores *aux){
    aux->primeira = malloc(sizeof(Identificador));
    aux->primeira->proxima = NULL;
    aux->primeira->anterior = NULL;
    aux->primeira->linha = 0;
    aux->primeira->coluna = 0;
	aux->numIdentificadores = 0;
}

//Insere valores em uma lista.
void inserirTabelaIdentificadores(TabelaIdentificadores *f, char *tipo, char *nome, int _linha, int _coluna){
	Identificador *aux;
	aux = malloc(1*sizeof(Identificador));

    //printf("%ld -- %d %d\n",strlen(valor),LINHA,COLUNA);
    aux->tipo = malloc((strlen(tipo)+1)*(sizeof(char)));
    
	strcpy(aux->tipo,tipo);

    aux->nome = malloc((strlen(nome)+1)*(sizeof(char)));
	strcpy(aux->nome,nome);

    aux->valor = malloc(1);
    strcpy(aux->valor,"");

    aux->registrador = malloc(5*sizeof(char));
    sprintf(aux->registrador,"t%d",NUM_REGISTRADORES);
    NUM_REGISTRADORES++;
    //strcpy(aux->registrador,"");

    /*
    if(!strcmp(aux->valor,"")){
        aux->valor = realloc(aux->valor,4);
        strcpy(aux->valor,"xdd");
        printf("%s\n",aux->valor);
    }
    */

	aux->proxima = NULL;
    aux->anterior = NULL;
    aux->linha = _linha;
    aux->coluna = _coluna;

	if(tabelaVaziaIdentificadores(f)){
		f->primeira = aux;
        f->ultima = aux;
		f->numIdentificadores++;
	}else{
        aux->anterior = f->ultima;
        f->ultima->proxima = aux;
        f->ultima = aux;
		f->numIdentificadores++;
	}
}

int pilhaVaziaAssembly(PilhaAssembly *f){
	if(f->numElementosPilha == 0){
		return 1;
	}else{
		return 0;
	}
}

//Inicia uma celula para receber um lista.
void iniciarPilhaAssembly(PilhaAssembly *aux){
    aux->primeira = malloc(sizeof(ElementoPilhaAssembly));
    aux->primeira->proxima = NULL;
    aux->primeira->anterior = NULL;
	aux->numElementosPilha = 0;
}

//Insere valores em uma lista.
void inserirPilhaAssembly(PilhaAssembly *f, char *comando, char *arg1, char *arg2, char *arg3){
	ElementoPilhaAssembly *aux;
	aux = malloc(1*sizeof(ElementoPilhaAssembly));

    //printf("%ld -- %d %d\n",strlen(valor),LINHA,COLUNA);
    aux->comando = malloc((strlen(comando)+1)*(sizeof(char)));  
	strcpy(aux->comando,comando);

    aux->arg1 = malloc((strlen(arg1)+1)*(sizeof(char)));
	strcpy(aux->arg1,arg1);

    aux->arg2 = malloc((strlen(arg2)+1)*(sizeof(char)));
	strcpy(aux->arg2,arg2);

    aux->arg3 = malloc((strlen(arg3)+1)*(sizeof(char)));
	strcpy(aux->arg3,arg3);

	aux->proxima = NULL;
    aux->anterior = NULL;

	if(pilhaVaziaAssembly(f)){
		f->primeira = aux;
        f->ultima = aux;
		f->numElementosPilha++;
	}else{
        aux->anterior = f->ultima;
        f->ultima->proxima = aux;
        f->ultima = aux;
		f->numElementosPilha++;
	}
}

void desempilharPilhaAssembly(PilhaAssembly *f){
    if(pilhaVaziaAssembly(f)){
        return;
    }

    //Pilha vai ficar vazia
    if(f->ultima->anterior == NULL){
        free(f->ultima);
        f->ultima = NULL;
        f->primeira = NULL;
        f->numElementosPilha = 0;
    }else{
        ElementoPilhaAssembly *aux = f->ultima;
        f->ultima = f->ultima->anterior;
        free(aux);
        f->numElementosPilha--;
    }
}

void printfPilhaAssembly(PilhaAssembly *f){
    if(pilhaVaziaAssembly(f)){
        printf("Pilha vazia.\n");
        return;
    }
    ElementoPilhaAssembly *aux = f->primeira;
    while(aux != NULL){
        printf("%s\n",aux->comando);
        aux = aux->proxima;
    }
}

void setEstadoFinal(MaquinaEstados *maquinaEstados, int estado){
    maquinaEstados->estados[estado].final = 1;
}

void freePalavrasReservadas(char **palavrasReservadas){
    int i;
    for(i=0;i<32;i++){
        printf("%p\n",&palavrasReservadas[i]);
        free(&palavrasReservadas[i]);
    }
    free(palavrasReservadas);
}

void freeListaToken(ListaToken *listaToken){
    if(listaToken == NULL){
        return;
    }

    Token *aux = listaToken->primeira;
    if(aux == NULL){
        return;
    }

    Token *aux2 = aux->proxima;
    while(aux2 != NULL){
        //printf("%s\n",aux->valorBruto);
        free(aux->valor);
        free(aux->valorBruto);
        free(aux);
        aux = aux2;
        aux2 = aux2->proxima;
    }
    //printf("%s\n",aux->valorBruto);
    free(aux);
}

void freeMaquinaEstados(MaquinaEstados *maquinaEstados){
    int i;
    if(maquinaEstados == NULL){
        return;
    }
    Estado *estado_aux;
    Transicao *aux,*aux2;
    for(i=0;i<NUM_ESTADOS;i++){
        //printf("-----Estado %d\n",i);
        estado_aux = &maquinaEstados->estados[i];
        
        if(estado_aux == NULL){
            continue;
        }

        aux = estado_aux->primeira;
        if(aux == NULL){
            continue;
        }

        aux2 = aux->proxima;
        while(aux2 != NULL){
            //printf("[%s]\n",aux->conjunto);
            free(aux->conjunto);
            free(aux);
            aux = aux2;
            aux2 = aux2->proxima;
        }
        //printf("{%s}\n",aux->conjunto);
        free(aux);
        //printf("\n");

        //free(estado_aux);
    }
    //printf("Maquina estados xd\n");
    free(maquinaEstados);
}

