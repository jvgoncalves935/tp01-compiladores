#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Biblioteca necessária para utilização do getopt().
#include "../headers/utils.h"
#include "../headers/lexico.h"
#include "../headers/automato.h"

int main(int argc,char **argv){
    // Função getopt(), (entrada por parâmetros).
	
	int optc = 0;
	char *argv1 = NULL;
	
	while((optc = getopt(argc, argv, "hc:a:")) != -1){
		switch(optc){
			case 'a':
				argv1 = optarg;
				break;
			case 'h':
				printf("%s -h \"Ajuda\".\nExemplo de entrada:\n./tp1 -a ARQUIVO\n-a arquivo .c para "
				"análise.\n",argv[0]);
				exit(0);
			default:
				printf("Opção inválida.\nUtilize -h para ajuda.\n");
				exit(0);
		}
	}
	if(argc < 2){
		printf("Nenhum arquivo foi inserido.\nUtilize o parâmetro -h para ajuda.\n");
		exit(0);
	}

    int i;
    //char tabela_ascii[TAM_ASCII];
    //char comentario = '//';
    //char literal = ''','"';
    

    char **palavras_reservadas = malloc(32*(sizeof(char *)));
    for(i=0;i<28;i++){
        palavras_reservadas[i] = malloc(15*sizeof(char));
    }

    //iniciarPalavrasReservadas(palavras_reservadas);
    //iniciarTabelaAscii(tabela_ascii);

    char temp;
    int tamanho_arquivo = 0;

    //Descobrir tamanho do arquivo
    FILE *arq = fopen(argv1,"r");
    while(fscanf(arq,"%c",&temp)!=EOF){
        tamanho_arquivo++;
    }
    fclose(arq);

    //Armazenar o arquivo em vetor
    char *arquivo = malloc(tamanho_arquivo*sizeof(char));
    arq = fopen(argv1,"r");
    i=0;
    while(fscanf(arq,"%c",&temp)!=EOF){
        arquivo[i] = temp;
        i++;
    }
    i=0;
    fclose(arq);

    for(i=0;i<tamanho_arquivo;i++){
        printf("%c",arquivo[i]);
    }
    free(arquivo);

    //Iniciar autômato.
    MaquinaEstados automato = iniciarAutomato();
    return 0;
}