#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include "gerencia_contas.h"


int main(int argc, char * argv[]){
	struct usuario usuario_corrente;

	if (argc < 3) {
		printf("Escolha uma opcao valida.\n");
		printf("Para utilizar o programa escreva no terminal:\n- Para ler algum usuario cadastrado: ./sistema_contas -l usuarios.txt <nome do usuario>\n- Para cadastrar o usuario: ./sistema_contas -m usuarios.txt <nome do usuario> <senha>\n");
		return -1;
	}
	if(argv[1][0]=='-'){
		switch(argv[1][1]){
			case 'l':
				usuario_corrente = leUsuario(argv[2],argv[3]);
				printf("ID: %d, usuario: %s, senha:%s\n", usuario_corrente.id, usuario_corrente.nome, usuario_corrente.senha);
			break;
			case 'm':
				usuario_corrente.id = adicionaUsuario(argv[2],argv[3],argv[4]);
				//printf("ID: %d\n", usuario_corrente.id);
			
			break;
			defaut:
				printf("Escolha uma opcao valida.\n");
				printf("Para utilizar o programa escreva:\nPara ler algum usuario cadastrado: ./sistema_contas -l usuarios.txt <nome do usuario>\nPara cadastrar o usuario: ./sistema_contas -m usuarios.txt <nome do usuario> <senha>\n");

		}
	}
	
	else {
		printf("Para utilizar o programa escreva:\nPara ler algum usuario cadastrado: ./sistema_contas -l usuarios.txt <nome do usuario>\nPara cadastrar o usuario: ./sistema_contas -m usuarios.txt <nome do usuario> <senha>\n");
	}
}