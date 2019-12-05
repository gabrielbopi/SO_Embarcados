#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <unistd.h>
#include "gerencia_contas.h"
#include <time.h>
#include "gpio_sysfs.h"

#define TEMPO_CREDITOS 5
#define entrada_usuario argv[3]
#define entrada_senha argv[4]

int recolheDigital(void);
int abreTranca(void);

int main(int argc, char* const argv[]){
	int socket_id;
	struct sockaddr_in servidorAddr;
	int length;
	unsigned short servidorPorta;
	char *IP_Servidor;
	char *mensagem;
	int resposta;
	time_t time_1, time_2;

	const int creditos_minimos = 5;
	struct usuario usuario_corrente;
	int polegarAutenticado;

	if (argc < 3){
		printf("Escolha uma opcao valida.\n");
		printf("Para utilizar o programa escreva no terminal:\n./cliente_terminal <IP do Servidor> <Porta do servidor> <nome do usuario> <senha do usuario>\n");
		return -1;
	}

	strcpy(usuario_corrente.nome, entrada_usuario);
	strcpy(usuario_corrente.senha, entrada_senha);

	IP_Servidor = argv[1];
	servidorPorta = atoi(argv[2]);
	//mensagem = argv[3];

	// Abrindo o socket para o cliente
	socket_id = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(socket_id < 0){
		fprintf(stderr, "Erro na criacao do Soquete!\n");
		exit(0);
	}

	// Conectando o socket ao IP "IP_Servidor" pela porta "servidorPorta"
	memset(&servidorAddr, 0, sizeof(servidorAddr));
	servidorAddr.sin_family = AF_INET;
	servidorAddr.sin_addr.s_addr = inet_addr(IP_Servidor);
	servidorAddr.sin_port =  htons(servidorPorta);
	if(connect(socket_id, (struct sockaddr *) &servidorAddr, sizeof(servidorAddr)) < 0){
		fprintf(stderr, "Erro na conexao!\n");
		exit(0);
	}

	// Mandando mensagem ao servidor
	length = sizeof(struct usuario);
	//write(socket_id, &length, sizeof(length));
	write(socket_id, &usuario_corrente, length);
	read(socket_id, &resposta, sizeof(resposta));
	//fprintf(stderr, "%d bytes.", length);
	read(socket_id, &usuario_corrente, length);
	// Fechando o socket local
	close(socket_id);

	if(resposta == 1){
		printf("ID: %d, usuario: %s, senha:%s, creditos:%d\n",
				usuario_corrente.id, usuario_corrente.nome, usuario_corrente.senha, usuario_corrente.creditos);
		abreTranca();	
		//polegarAutenticado = recolheDigital()/256;
		//	printf("Resposta: %d\n", polegarAutenticado);

		if(polegarAutenticado == 10) {
				abreTranca();
				printf("Abre-te Sesamo!\n");
			}
							time_1 = time(NULL);

		while(1){
			time_2 = time(NULL);
			printf("Creditos restantes: %d\n", usuario_corrente.creditos--);
			printf("Tempo de uso do guarda volumes: %4.0f s\n", difftime(time_2, time_1));
			sleep(TEMPO_CREDITOS);
		}
	}
	else if(resposta == 2)	{printf("Senha incorreta!\n");}
	else if(resposta == 0)	{printf("Usuario escrito escrito errado ou inexistente.\n");}
	else {printf("Erro no servidor.\n");}

	return 0;
}


int recolheDigital(void){
	int resposta;

	resposta = system("python /home/pi/Desktop/Codigo/fingerprint_enroll.py");
	printf("Resposta: %d\n", resposta);
	return resposta;
}

int abreTranca(void){
	int pin=4;
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

