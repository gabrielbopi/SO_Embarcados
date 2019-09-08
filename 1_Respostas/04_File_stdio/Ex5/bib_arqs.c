#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

char* le_arq_texto(char *nome_arquivo)
{
    FILE *fp;
	int i;
	char *nome;
	char letra;

	nome = (char *) malloc(tam_arq_texto(nome_arquivo));
    fp = fopen(nome_arquivo,"r");
    if(!fp){
        printf("Erro ao abrir o arquivo!");
        exit(EXIT_FAILURE);
    }
	for(i=0; (letra=getc(fp)) != EOF ; i++)	nome[i] = letra;
    fclose(fp);
	printf("%s\n", nome);
	free(nome);
    return nome;
}