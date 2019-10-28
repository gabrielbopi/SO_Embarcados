#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gerencia_contas.h"
#include "gpio_sysfs.h"
#include <unistd.h>
#define ARQUIVO_CONTAS	"usuarios.txt"
#define entrada_usuario argv[2]
#define entrada_senha argv[3]

int abreTranca(void);

int main(int argc, char * argv[]){
	const int creditos_minimos = 5;
	struct usuario usuario_corrente;

	if (argc < 3) {
		printf("Escolha uma opcao valida.\n");
		printf("Para utilizar o programa escreva no terminal:\n./sistema_contas -a <nome do usuario> <senha do usuario>\n");
		return -1;
	}
	if(argv[1][0]=='-'){
		switch(argv[1][1]){
			case 'a':
				usuario_corrente = leUsuario(ARQUIVO_CONTAS,entrada_usuario);
				//printf("Usuario digitado: %s, senha digitada:%s\n", entrada_usuario, entrada_senha);
				//printf("ID: %d, usuario: %s, senha:%s, creditos: %d\n", usuario_corrente.id, usuario_corrente.nome, usuario_corrente.senha, usuario_corrente.creditos);
				if (strcmp(entrada_usuario, usuario_corrente.nome) == 0){
					if (strcmp(entrada_senha, usuario_corrente.senha) == 0){
						//FUNÇÃO PARA ABRIR A TRANCA AQUI!
						if (usuario_corrente.creditos >= creditos_minimos){
							printf("Abre-te Sesamo!\n");
							abreTranca();
						}
						else{
							printf("Não é possivel utilizar o sistema, usurio sem creditos o suficiente. (Pelo menos %d creditos)\n", creditos_minimos);

						}
					}
					else{
							printf("Senha incorreta!\n");
					}
				}
				else{
					printf("Usuario nao encontrado.\n");
					}
			break;
			/*case 'm':
				usuario_corrente.id = adicionaUsuario(argv[2],argv[3],argv[4]);
				//printf("ID: %d\n", usuario_corrente.id);
			
			break;*/
			defaut:
				printf("Escolha uma opcao valida.\n");
		printf("Para utilizar o programa escreva no terminal:\n./sistema_contas -a <nome do usuario> <senha do usuario>\n");

		}
	}
	
	else {
		printf("Para utilizar o programa escreva no terminal:\n./sistema_contas -a <nome do usuario> <senha do usuario>\n");
	}
}


int abreTranca(void){
	int pin=21;
	if(setGPIO_Out(pin)){
		printf("Erro ao tentar abrir a porta...(1)\n");
		return -1;
	}
	if (GPIO_Write(pin,1)){
		printf("Erro ao tentar abrir a porta...(2)\n");
		return 1;
		}
	printf("Tranca abre...\n");
	sleep(6);
	if (GPIO_Write(pin,0)){
		printf("Erro ao tentar desligar a tranca...(1)\n");
		return 3;
		}
	if(unsetGPIO(pin)){
		printf("Erro ao tentar desligar a tranca...(2)\n");
		return 2;
	}
	return 0;
}
