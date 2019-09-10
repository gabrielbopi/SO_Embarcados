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

    	fp = open(nome_arquivo, O_RDONLY);
    if(fp == -1){
        printf("Erro ao abrir o arquivo!");
        exit(EXIT_FAILURE);
    }
	while((read(fp,&caractere,sizeof(char)) != 0) & tamanho_bytes <50){//<-O ERRO ACONTECE AQUI!!
		tamanho_bytes++;
		//printf("\n%d",caractere);
	}
    	close(fp);
    	return tamanho_bytes;
}

char* le_arq_texto(char *nome_arquivo){
    	int fp;
	int i;
	char *nome;
	char letra;

	nome = (char *) malloc(tam_arq_texto(nome_arquivo));
    	fp = open(nome_arquivo,O_RDONLY | O_CREAT/*, S_IRWXU*/);
    	if(fp == -1){
        	printf("Erro ao abrir o arquivo!");
        	exit(EXIT_FAILURE);
    	}
	read(fp,&letra,1);
	for(i=0; letra != EOF ; i++) {nome[i] = letra;}
    	close(fp);
	printf("%s\n", nome);
	
    	return nome;
	free(nome);
}
