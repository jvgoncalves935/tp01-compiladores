#include <stdio.h>
#include "../headers/utils.h"
#include "../headers/lexico.h"

void criarEstado(Estado *estado, int idEstado){
    estado->id = idEstado;
    estado->numTransicoes = 0;
    iniciarLista(estado);
}

void adicionarTransicao(MaquinaEstados *maquinaEstados, int idTransicao, char *conjunto){
    //Estado *e = malloc(sizeof(Estado));
}

void alimentarMaquinaEstados(MaquinaEstados *maquinaEstados, char token, int *valido, char **palavrasReservadas, ListaToken *listaToken){
    int i;
    Transicao *aux = maquinaEstados->estados[maquinaEstados->estadoAtual].primeira;
    int achou = 0;
    for(i=0;i<maquinaEstados->estados[maquinaEstados->estadoAtual].numTransicoes;i++){
        int j;
        for(j=0;aux->conjunto[j]!='\0';j++){
            if(aux->conjunto[j] == token){
                maquinaEstados->estadoAtual = aux->proximoEstado;
                if(strchr(SEPARADOR,token) == NULL){
                    sprintf(BUFFER,"%s%c",BUFFER,token);
                }else{
                    identificarToken(maquinaEstados,palavrasReservadas,listaToken);
                    sprintf(BUFFER,"%c",token);
                    identificarToken(maquinaEstados,palavrasReservadas,listaToken);
                }
                achou = 1;
                break;
            }
        }
        if(achou){
            break;
        }
        aux = aux->proxima;
    }
    if(!achou){
        (*valido) = 0; 
    }
}

void iniciarAutomato(MaquinaEstados *maquinaEstados){
    setEstadoFinal(maquinaEstados,0);
    inserirLista(&maquinaEstados->estados[0],"$",1);
    inserirLista(&maquinaEstados->estados[0],"_",1);
    inserirLista(&maquinaEstados->estados[0],LETRA,1);
    inserirLista(&maquinaEstados->estados[0],SEPARADOR,0);
    inserirLista(&maquinaEstados->estados[0],NUMERO,2);
    inserirLista(&maquinaEstados->estados[0],"+",4);
    inserirLista(&maquinaEstados->estados[0],"-",5);
    inserirLista(&maquinaEstados->estados[0],"*",6);
    inserirLista(&maquinaEstados->estados[0],"/",7);
    inserirLista(&maquinaEstados->estados[0],"=",8);
    inserirLista(&maquinaEstados->estados[0],"<",9);
    inserirLista(&maquinaEstados->estados[0],">",10);
    inserirLista(&maquinaEstados->estados[0],"%",11);
    inserirLista(&maquinaEstados->estados[0],"!",13);
    inserirLista(&maquinaEstados->estados[0],"~",13);
    inserirLista(&maquinaEstados->estados[0],"^",13);
    inserirLista(&maquinaEstados->estados[0],"?",13);
    inserirLista(&maquinaEstados->estados[0],"|",14);
    inserirLista(&maquinaEstados->estados[0],"&",15);
    inserirLista(&maquinaEstados->estados[0],"\"",16);
    

    inserirLista(&maquinaEstados->estados[1],LETRA,1);
    inserirLista(&maquinaEstados->estados[1],"_",1);
    inserirLista(&maquinaEstados->estados[1],NUMERO,1);
    inserirLista(&maquinaEstados->estados[1],SEPARADOR,0);

    inserirLista(&maquinaEstados->estados[2],NUMERO,3);
    inserirLista(&maquinaEstados->estados[2],".",3);
    inserirLista(&maquinaEstados->estados[2],SEPARADOR,0);

    inserirLista(&maquinaEstados->estados[3],NUMERO,3);
    inserirLista(&maquinaEstados->estados[3],SEPARADOR,0);

    inserirLista(&maquinaEstados->estados[4],SEPARADOR,0);
    inserirLista(&maquinaEstados->estados[4],"+",0);
    inserirLista(&maquinaEstados->estados[4],"=",0);

    inserirLista(&maquinaEstados->estados[5],SEPARADOR,0);
    inserirLista(&maquinaEstados->estados[5],"-",0);
    inserirLista(&maquinaEstados->estados[5],"=",0);
    
    inserirLista(&maquinaEstados->estados[6],SEPARADOR,0);
    inserirLista(&maquinaEstados->estados[6],"=",0);

    inserirLista(&maquinaEstados->estados[7],SEPARADOR,0);
    inserirLista(&maquinaEstados->estados[7],"=",0);

    inserirLista(&maquinaEstados->estados[8],SEPARADOR,0);
    inserirLista(&maquinaEstados->estados[8],"=",0);

    inserirLista(&maquinaEstados->estados[9],SEPARADOR,0);
    inserirLista(&maquinaEstados->estados[9],"=",0);

    inserirLista(&maquinaEstados->estados[10],SEPARADOR,0);
    inserirLista(&maquinaEstados->estados[10],"=",0);

    inserirLista(&maquinaEstados->estados[11],SEPARADOR,0);

    inserirLista(&maquinaEstados->estados[12],SEPARADOR,0);

    setEstadoFinal(maquinaEstados,13);
    inserirLista(&maquinaEstados->estados[13],SEPARADOR,0);
    inserirLista(&maquinaEstados->estados[13],LETRA,1);
    
    inserirLista(&maquinaEstados->estados[14],"|",0);
    
    inserirLista(&maquinaEstados->estados[15],"&",0);

    inserirLista(&maquinaEstados->estados[16],"\\",17);
    inserirLista(&maquinaEstados->estados[16],"\"",0);
    inserirLista(&maquinaEstados->estados[16],"'",16);
    inserirLista(&maquinaEstados->estados[16],LETRA,16);
    inserirLista(&maquinaEstados->estados[16],OPERADOR,16);
    inserirLista(&maquinaEstados->estados[16],SEPARADOR,16);
    inserirLista(&maquinaEstados->estados[16],NUMERO,16);
    
    inserirLista(&maquinaEstados->estados[17],LETRA,16);
    inserirLista(&maquinaEstados->estados[17],OPERADOR,16);
    inserirLista(&maquinaEstados->estados[17],SEPARADOR,16);
    inserirLista(&maquinaEstados->estados[17],NUMERO,16);
    inserirLista(&maquinaEstados->estados[17],"'",16);
    inserirLista(&maquinaEstados->estados[17],"\\",16);
    inserirLista(&maquinaEstados->estados[17],"\"",16);
    //inserirLista(&maquinaEstados->estados[],,);
    /*
    inserirLista(&maquinaEstados->estados[0],"#",19);

    inserirLista(&maquinaEstados->estados[1],LETRA,2);
    inserirLista(&maquinaEstados->estados[1],NUMERO,2);
    inserirLista(&maquinaEstados->estados[1]," ",3);
    inserirLista(&maquinaEstados->estados[1],"\n;",1);

    inserirLista(&maquinaEstados->estados[2],LETRA,2);
    inserirLista(&maquinaEstados->estados[2],NUMERO,2);
    inserirLista(&maquinaEstados->estados[2]," ",3);

    inserirLista(&maquinaEstados->estados[3],LETRA,4);
    inserirLista(&maquinaEstados->estados[3],OPERADOR,7);

    inserirLista(&maquinaEstados->estados[4],LETRA,5);
    inserirLista(&maquinaEstados->estados[4],NUMERO,5);

    inserirLista(&maquinaEstados->estados[5],LETRA,5);
    inserirLista(&maquinaEstados->estados[5],NUMERO,5);
    inserirLista(&maquinaEstados->estados[5],OPERADOR,6);

    inserirLista(&maquinaEstados->estados[6],"'",10);
    inserirLista(&maquinaEstados->estados[6],"\"",13);
    inserirLista(&maquinaEstados->estados[6],NUMERO,14);
    inserirLista(&maquinaEstados->estados[6],LETRA,15);

    inserirLista(&maquinaEstados->estados[7],OPERADOR,8);
    inserirLista(&maquinaEstados->estados[7],LETRA,9);

    inserirLista(&maquinaEstados->estados[8],NUMERO,16);
    
    inserirLista(&maquinaEstados->estados[9],LETRA,9);
    inserirLista(&maquinaEstados->estados[9],NUMERO,9);
    inserirLista(&maquinaEstados->estados[9],OPERADOR,17);

    inserirLista(&maquinaEstados->estados[10],LETRA,11);
    inserirLista(&maquinaEstados->estados[10],NUMERO,11);
    inserirLista(&maquinaEstados->estados[10],OPERADOR,11);

    inserirLista(&maquinaEstados->estados[11],"'",12);

    inserirLista(&maquinaEstados->estados[12],";",1);

    inserirLista(&maquinaEstados->estados[13],LETRA,13);
    inserirLista(&maquinaEstados->estados[13],NUMERO,13);
    inserirLista(&maquinaEstados->estados[13],OPERADOR,13);
    inserirLista(&maquinaEstados->estados[13],"\"",12);

    inserirLista(&maquinaEstados->estados[14],NUMERO,14);
    inserirLista(&maquinaEstados->estados[14],";",1);

    inserirLista(&maquinaEstados->estados[15],";",1);

    inserirLista(&maquinaEstados->estados[16],NUMERO,16);
    inserirLista(&maquinaEstados->estados[16],";",1);

    inserirLista(&maquinaEstados->estados[17],NUMERO,16);
    inserirLista(&maquinaEstados->estados[17],LETRA,18);

    inserirLista(&maquinaEstados->estados[18],LETRA,18);
    inserirLista(&maquinaEstados->estados[18],NUMERO,18);
    inserirLista(&maquinaEstados->estados[18],";",1);

    inserirLista(&maquinaEstados->estados[19],"i",20);

    inserirLista(&maquinaEstados->estados[20],"n",21);

    inserirLista(&maquinaEstados->estados[21],"c",22);

    inserirLista(&maquinaEstados->estados[22],"l",23);
    
    inserirLista(&maquinaEstados->estados[23],"u",24);

    inserirLista(&maquinaEstados->estados[24],"d",25);

    inserirLista(&maquinaEstados->estados[25],"e",26);

    inserirLista(&maquinaEstados->estados[26]," ",27);

    inserirLista(&maquinaEstados->estados[27],"<",28);
    inserirLista(&maquinaEstados->estados[27],"\"",29);

    inserirLista(&maquinaEstados->estados[28],"/",28);
    inserirLista(&maquinaEstados->estados[28],".",28);
    inserirLista(&maquinaEstados->estados[28],LETRA,28);
    inserirLista(&maquinaEstados->estados[28],">",30);

    inserirLista(&maquinaEstados->estados[29],"/",29);
    inserirLista(&maquinaEstados->estados[29],".",29);
    inserirLista(&maquinaEstados->estados[29],LETRA,29);
    inserirLista(&maquinaEstados->estados[29],"\"",30);

    inserirLista(&maquinaEstados->estados[30],"\n",31);

    inserirLista(&maquinaEstados->estados[31],"#",19);
    inserirLista(&maquinaEstados->estados[31],LETRA,1);
    //inserirLista(&maquinaEstados->estados[],,);
    */
}
