//Servidor central para gerenciamento dos usuarios
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netdb.h>
#include "gerencia_contas.h"
#define ARQUIVO_CONTAS	"usuarios.txt"

int socket_id;
void sigint_handler(int signum);
void procuraUsuario(int client_socket);
void end_server(void);
char *get_ip(char *host);

int main (int argc, char* const argv[]){
	unsigned short servidorPorta;
	struct sockaddr_in servidorAddr;
	char *servidorIP,*ip;

	if (argc < 3) {
		printf("Escolha uma opcao valida.\n");
		printf("Para utilizar o programa escreva no terminal:\n$ ./servidor_sistema <IP do servidor> <Porta do servidor>\n");
		return -1;
	}
	// Definindo o tratamento de SIGINT
	servidorIP = argv[1];
	servidorPorta = atoi(argv[2]);
	signal(SIGINT, sigint_handler);

	// Abrindo o socket local
	socket_id = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(socket_id < 0)
	{
		fprintf(stderr, "Erro na criacao do Soquete!\n");
		exit(-1);
	}
	ip = get_ip(servidorIP);
	// Ligando o socket a porta "servidorPorta"
	memset(&servidorAddr, 0, sizeof(servidorAddr));
	servidorAddr.sin_family = AF_INET;
	servidorAddr.sin_addr.s_addr = inet_addr(ip);//htonl(INADDR_ANY);
	//printf("servidorAddr.sin_addr.s_addr = %d\n",servidorAddr.sin_addr.s_addr);
	servidorAddr.sin_port = htons(servidorPorta);
	if(bind(socket_id, (struct sockaddr *) &servidorAddr, sizeof(servidorAddr)) < 0){
		fprintf(stderr, "Erro na ligacao!\n");
		exit(-1);
	}
	// Tornando o socket passivo (para virar um servidor)
	if(listen(socket_id,10) < 0){
		fprintf(stderr, "Erro!\n");
		exit(0);
	}

	while(1){
		int socketCliente;
		struct sockaddr_in clienteAddr;
		unsigned int clienteLength;
		// Aguardando a conexao de um cliente
		clienteLength = sizeof(clienteAddr);
		if((socketCliente = accept(socket_id, (struct sockaddr *) &clienteAddr, &clienteLength)) < 0)
		{	fprintf(stderr, "Falha no accept().\n");}

		fprintf(stderr, "Conexao do Cliente %s\n", inet_ntoa(clienteAddr.sin_addr));
		// Tratando comunicacao com o cliente
		procuraUsuario(socketCliente);
		// Fechando a conexao com o cliente
		close(socketCliente);
	}

	return 0;
}

void sigint_handler(int signum){
	fprintf(stderr, "\nRecebido o sinal CTRL+C... vamos desligar o servidor!\n");
	end_server();
}

void procuraUsuario(int client_socket){
	int length, nome_valido, senha_valida;
	char* text;
	struct usuario usuario_solicitado, usuario_corrente;
	int resposta = 0;

	length = sizeof(struct usuario);
	//fprintf(stderr, "\nMensagem enviada pelo cliente tem ");
	//read(client_socket, &length, sizeof(length));
	//fprintf(stderr, "%d bytes.", length);
	//text = (char*) malloc (length);
	read(client_socket, &usuario_solicitado, length);
	usuario_corrente = leUsuario(ARQUIVO_CONTAS,usuario_solicitado.nome);

	nome_valido = strcmp(usuario_solicitado.nome, usuario_corrente.nome);
	senha_valida = strcmp(usuario_solicitado.senha, usuario_corrente.senha);

	if(nome_valido == 0){
		if(senha_valida == 0){
			resposta = 1;
			printf("ID: %d, usuario: %s, senha:%s, creditos:%d\n",
				usuario_corrente.id, usuario_corrente.nome, usuario_corrente.senha, usuario_corrente.creditos);
			write(client_socket, &resposta, sizeof(resposta));
			write(client_socket, &usuario_corrente, length);
		}else{
			resposta = 2;
			printf("ID: %d, usuario: %s\nSenha incorreta!\n",
				usuario_corrente.id, usuario_corrente.nome);
			write(client_socket, &resposta, sizeof(resposta));
		}
	}else{
		resposta = 0;
		printf("Usuario nao encontrado...\n");
		write(client_socket, &resposta, sizeof(resposta));
	}
	/*fprintf(stderr, "nMensagem = %s\n", text);
	if (!strcmp(text, "sair")){
		free (text);
		fprintf(stderr, "Cliente pediu para o servidor fechar.\n");
		end_server();
	}
	free(text);
	*/
}

void end_server(void){
	//Fechando o socket local
	close(socket_id);
	exit(0);
}

char *get_ip(char *host)
{
	struct hostent *hent;
	int iplen = 15; //XXX.XXX.XXX.XXX
	char *ip = (char *)malloc(iplen+1);
	memset(ip, 0, iplen+1);
	if((hent = gethostbyname(host)) == NULL)
	{
		herror("Can't get IP");
		exit(1);
	}
	if(inet_ntop(AF_INET, (void *)hent->h_addr_list[0], ip, iplen) == NULL)
	{
		perror("Can't resolve host");
		exit(1);
	}
	return ip;
}
