#include <stdio.h>
#include <stdlib.h>
#include "bib_arqs.h"

int tam_arq_texto(char *nome_arquivo)
{
    FILE *fp;
	int i, tamanho_bytes;

    fp = fopen(nome_arquivo,"r");
    if(!fp){
        printf("Erro ao abrir o arquivo!");
        exit(EXIT_FAILURE);
    }
	while(i=getc(fp) != EOF)	tamanho_bytes++;
    fclose(fp);
    return tamanho_bytes;
}
