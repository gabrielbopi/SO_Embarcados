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
	char *mensagem[] ={"Pai, é a verdadeira essencia da sabedoria?","Mas ate uma crianca de tres anos sabe disso!"};
	char *text;

	if (argc < 3)
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
		//0
		length = strlen(mensagem[0]) + 1;
		write(socket_id, &length, sizeof(length));
		write(socket_id, mensagem[0], length);
		//fprintf(stderr,"tamanho do texto env: %d\n\n", length);
		read(socket_id, &length, sizeof (length));
		text = (char*) malloc (length);
		//fprintf(stderr,"tamanho do texto rec: %d\n\n", length);
		read(socket_id, text, length);
		fprintf(stderr,"Pai: %s\n\n", text);
		free (text);
		//1
		length = strlen(mensagem[1]) + 1;
		write(socket_id, &length, sizeof(length));
		write(socket_id, mensagem[1], length);
		//fprintf(stderr,"tamanho do texto env: %d\n\n", length);
		read(socket_id, &length, sizeof (length));
		text = (char*) malloc (length);
		//fprintf(stderr,"tamanho do texto rec: %d\n\n", length);
		read(socket_id, text, length);
		fprintf(stderr,"Pai: %s\n\n", text);
		free (text);
		
	// Fechando o socket local
	close(socket_id);
	return 0;
}
