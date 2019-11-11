//Servidor central para gerenciamento dos usuarios
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "gerencia_contas.h"
#define ARQUIVO_CONTAS	"usuarios.txt"

int socket_id;
void sigint_handler(int signum);
void procuraUsuario(int client_socket);
void end_server(void);

int main (int argc, char* const argv[]){
	unsigned short servidorPorta;
	struct sockaddr_in servidorAddr;

	if (argc < 3) {
		printf("Escolha uma opcao valida.\n");
		printf("Para utilizar o programa escreva no terminal:\n$ ./servidor_sistema <IP do Servidor> <Porta do servidor>\n");
		return -1;
	}
	// Definindo o tratamento de SIGINT
	servidorPorta = atoi(argv[1]);
	signal(SIGINT, sigint_handler);

	// Abrindo o socket local
	socket_id = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(socket_id < 0)
	{
		fprintf(stderr, "Erro na criacao do Soquete!\n");
		exit(-1);
	}
	// Ligando o socket a porta "servidorPorta"
	memset(&servidorAddr, 0, sizeof(servidorAddr));
	servidorAddr.sin_family = AF_INET;
	servidorAddr.sin_addr.s_addr = htonl(INADDR_ANY);
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
		}
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