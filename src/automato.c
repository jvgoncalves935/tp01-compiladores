#include <stdio.h>
#include "../headers/utils.h"

void criarEstado(Estado *estado, int idEstado){
    estado->id = idEstado;
    estado->numTransicoes = 0;
    iniciarLista(estado);
}

void adicionarTransicao(MaquinaEstados *maquinaEstados, int idTransicao, char *conjunto){
    //Estado *e = malloc(sizeof(Estado));
}

void iniciarAutomato(MaquinaEstados *maquinaEstados){
    inserirLista(&maquinaEstados->estados[0],"#",strlen("#"),19);

    inserirLista(&maquinaEstados->estados[1],LETRA,strlen(LETRA),2);
    inserirLista(&maquinaEstados->estados[1],NUMERO,strlen(NUMERO),2);
    inserirLista(&maquinaEstados->estados[1]," ",strlen(" "),3);

    inserirLista(&maquinaEstados->estados[2],LETRA,strlen(LETRA),2);
    inserirLista(&maquinaEstados->estados[2],NUMERO,strlen(NUMERO),2);
    inserirLista(&maquinaEstados->estados[2]," ",strlen(" "),3);


}
