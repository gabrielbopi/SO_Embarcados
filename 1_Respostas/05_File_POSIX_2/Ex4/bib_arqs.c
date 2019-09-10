#include <stdio.h>
#include <stdlib.h>
#include "bib_arqs.h"
#include <fcntl.h>
#include <unistd.h>

int tam_arq_texto(char *nome_arquivo)
{
    	int fp;
	int i, tamanho_bytes;
	char caractere;

    	fp = open(nome_arquivo,O_RDONLY | O_CREAT, S_IRWXU);
    if(fp == -1){
        printf("Erro ao abrir o arquivo!");
        exit(EXIT_FAILURE);
    }
	while(i=read(fp,&caractere,1) != EOF)	tamanho_bytes++;
    close(fp);
    return tamanho_bytes;
}
