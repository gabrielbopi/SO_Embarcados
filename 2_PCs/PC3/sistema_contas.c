#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#define entrada_arquivo argv[2]
#define entrada_usuario argv[3]
#define entrada_senha argv[4]
#define entrada_creditos argv[5]

#include "gerencia_contas.h"


int main(int argc, char * argv[]){
	struct usuario usuario_corrente;
	int sucesso;

	if (argc < 3) {
		printf("Escolha uma opcao valida.\n");
		printf("Para utilizar o programa escreva no terminal:\n- Para ler algum usuario cadastrado: ./sistema_contas -l usuarios.txt <nome do usuario>\n- Para cadastrar o usuario: ./sistema_contas -m usuarios.txt <nome do usuario> <senha> <numero de creditos>\n");
		return -1;
	}
	if(argv[1][0]=='-'){
		switch(argv[1][1]){
			case 'l':
				usuario_corrente = leUsuario(entrada_arquivo,entrada_usuario);
				printf("ID: %d, usuario: %s, senha:%s, creditos:%d\n", usuario_corrente.id, usuario_corrente.nome, usuario_corrente.senha, usuario_corrente.creditos);
			break;
			case 'm':
				if (argc < 5) {
		printf("Escolha uma opcao valida.\n");
		printf("Para utilizar o programa escreva:\nPara ler algum usuario cadastrado: ./sistema_contas -l usuarios.txt <nome do usuario>\nPara cadastrar o usuario: ./sistema_contas -m usuarios.txt <nome do usuario> <senha> <numero de creditos>\n");
		return -1;
				}
				sucesso = adicionaUsuario(entrada_arquivo,entrada_usuario,entrada_senha, atoi(entrada_creditos));
				if (sucesso != 0) {printf("Erro no cadastro!\n");}
				//printf("ID: %d\n", usuario_corrente.id);
			break;
			defaut:
				printf("Escolha uma opcao valida.\n");
		printf("Para utilizar o programa escreva:\nPara ler algum usuario cadastrado: ./sistema_contas -l usuarios.txt <nome do usuario>\nPara cadastrar o usuario: ./sistema_contas -m usuarios.txt <nome do usuario> <senha> <numero de creditos>\n");

		}
	}
	
	else {
		printf("Para utilizar o programa escreva:\nPara ler algum usuario cadastrado: ./sistema_contas -l usuarios.txt <nome do usuario>\nPara cadastrar o usuario: ./sistema_contas -m usuarios.txt <nome do usuario> <senha> <numero de creditos>\n");
	}
}
