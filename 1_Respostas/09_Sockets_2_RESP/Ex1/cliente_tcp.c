#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <unistd.h>

int main (int argc, char* const argv[])
{
	int socket_id;
	struct sockaddr_in servidorAddr;
	int i, length;
	unsigned short servidorPorta;
	char *IP_Servidor;
	char *mensagem[] ={"1","2","3","4","5","6","7","8","9","10"};

	if (argc != 4)
	{
		puts("   Modo de Uso:");
		printf("      %s <IP do Servidor> <Porta do servidor>\n", argv[0]);
		printf("   Exemplo: %s 127.0.0.1 8000\n", argv[0]);
		exit(1);
	}
	IP_Servidor = argv[1];
	servidorPorta = atoi(argv[2]);
	//mensagem = argv[3];

	// Abrindo o socket para o cliente
	socket_id = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(socket_id < 0)
	{
		fprintf(stderr, "Erro na criacao do socket!\n");
		exit(0);
	}
	
	// Conectando o socket ao IP "IP_Servidor" pela porta "servidorPorta"
	memset(&servidorAddr, 0, sizeof(servidorAddr)); // Zerando a estrutura de dados
	servidorAddr.sin_family = AF_INET;
	servidorAddr.sin_addr.s_addr = inet_addr(IP_Servidor);
	servidorAddr.sin_port = htons(servidorPorta);
	if(connect(socket_id, (struct sockaddr *) &servidorAddr, 
							sizeof(servidorAddr)) < 0)
	{
		fprintf(stderr, "Erro na conexao!\n");
		exit(0);
	}

	// Mandando mensagem ao servidor
	for(i=0; i<10 ;i++){
		printf("i = %d\n", i);
		length = strlen(mensagem[i]) + 1;
		printf("length: %d\n", length);
		write(socket_id, &length, sizeof(length));
		write(socket_id, mensagem[i], length);
		printf("Mandado: %s\n", mensagem[i]);
		sleep(1);
	}
	// Fechando o socket local
	close(socket_id);
	return 0;
}
