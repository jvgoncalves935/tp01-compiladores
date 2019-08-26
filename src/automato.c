#include <stdio.h>
#include "../headers/automato.h"
#include "../headers/utils.h"

MaquinaEstados iniciarAutomato(){
    MaquinaEstados automato;
    automato.estadoAtual = ' ';
    return automato;
}

void adicionarTransicao(int idTransicao, char *conjunto){
    //usar strcpy
}
