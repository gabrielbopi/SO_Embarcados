#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
//#include "bib_arqs.h"
#include "gerencia_contas.h"

/*struct usuario
{
	int id;
	char nome[30], senha[30];
	int creditos; 
};*/

struct usuario leUsuario(char *nome_arquivo, char *nome_usuario){
    int fp;
	char i;
	struct usuario usuario_corrente;

	int offset1, offset2;
	usuario_corrente.id = 0;

    fp = open(nome_arquivo,O_RDONLY | O_CREAT, S_IRWXU);
    if(fp == -1){
       	printf("Erro ao abrir o arquivo!");
       	exit(EXIT_FAILURE);
    }

    offset2 = sizeof(usuario_corrente.senha) + sizeof(usuario_corrente.creditos);

	while(read(fp, &i, sizeof(char)) != 0) {
	    offset1 = usuario_corrente.id*sizeof(struct usuario) + sizeof(int);
	    lseek(fp, offset1, SEEK_SET);
	    //printf("usuario_corrente.nome:%s nome_usuario:%s\n", usuario_corrente.nome, nome_usuario);
	    read(fp, usuario_corrente.nome, 30 * sizeof(char));
		if (strcmp(usuario_corrente.nome, nome_usuario) == 0){
		    read(fp, usuario_corrente.senha, 30 * sizeof(char));
   		    read(fp, &usuario_corrente.creditos, sizeof(int));

			return usuario_corrente;
		}
		else{
			lseek(fp, offset2, SEEK_CUR);
			usuario_corrente.id++;
		}
	}
	usuario_corrente.id = -1;
	strcpy(usuario_corrente.nome,"");
	strcpy(usuario_corrente.senha,"");
	usuario_corrente.creditos = 0;


	printf("Usuario nao existente anteriormente no sistema.\n");
   	return usuario_corrente;
}

int adicionaUsuario(char *nome_arquivo, char *nome_usuario,char *senha_usuario, int creditos_usuario){
    int fp;
	struct usuario usuario_corrente;

	usuario_corrente = leUsuario(nome_arquivo, nome_usuario);
	if(strcmp(usuario_corrente.nome, nome_usuario) == 0){
		printf("Erro. Esse usuario ja existe.\n" );
		return -1;
	}
	else{
		strcpy(usuario_corrente.nome,nome_usuario);
		strcpy(usuario_corrente.senha,senha_usuario);
		usuario_corrente.creditos = creditos_usuario;

		fp = open(nome_arquivo, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
    	if(fp == -1){
        	printf("Erro ao abrir o arquivo!");
        	exit(EXIT_FAILURE);
        }

        if(write(fp, &usuario_corrente, sizeof(struct usuario)) != -1){
   	    	printf("Usuario cadastrado com sucesso!\n");	
        }
    	else{
    		printf("Erro no cadastro de usuario!\n");
    		return -2;
    	}
   		return 0;
   	}
}



/*
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

char* le_arq_texto(char *nome_arquivo){
    	int fp;
	int i;
	char *nome;
	char letra;

	nome = (char *) malloc(tam_arq_texto(nome_arquivo));
    	fp = open(nome_arquivo,O_RDONLY | O_CREAT, S_IRWXU);

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
*/