#include "../headers/utils.h"
#include <stdio.h>

void analiseLexica(MaquinaEstados *maquinaEstados, char *arquivo){
    int tamArquivo = strlen(arquivo);
    int posicao;
    int valido = 1;
    
    for(posicao = 0;posicao<tamArquivo;posicao++){
        alimentarMaquinaEstados(maquinaEstados,arquivo[posicao],&valido);
        if(!valido){
            break;
        }
        if(arquivo[posicao] != '\n'){
            COLUNA++;
        }else{
            LINHA++;
            COLUNA = 1;
        }
    }

    if(valido){
        printf("Analise Lexica: SUCESSO. Sem erros.\n");
    }else{
        printf("Analise Lexica: ERRO. Linha %d, Coluna %d.\n",LINHA,COLUNA);
    }


}
