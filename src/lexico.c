#include "../headers/utils.h"

int LINHA = 0;
int COLUNA = 0;

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
            COLUNA = 0;
        }
    }

    if(valido){
        printf("Analise Lexica: SUCESSO. Sem erros.");
    }else{
        printf("Analise Lexica: ERRO. Linha %d, Coluna %d.",LINHA,COLUNA);
    }


}
