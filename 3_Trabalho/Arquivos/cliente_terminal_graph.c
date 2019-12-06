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
#include <gtk/gtk.h>


#define TEMPO_CREDITOS 5
#define entrada_usuario txt_usuario//argv[3]
#define entrada_senha txt_senha//argv[4]

int recolheDigital(void);
int abreTranca(void);

static int numero_entradas;
static char *IP_Servidor;
static int servidorPorta;
GtkWidget *txt_usuario, *txt_senha;

int login(GtkWidget *wid, gpointer ptr);


void end_program(GtkWidget *wid, gpointer ptr)
{
	gtk_main_quit();
}

void copy_text(GtkWidget *wid, gpointer ptr)
{
	// Obter o texto inserido
	// no campo de texto
	const char *input = gtk_entry_get_text(GTK_ENTRY(txt_usuario));
	// Atualizar o label com este texto 
	gtk_label_set_text(GTK_LABEL(ptr), input);
}



int main(int argc, char* argv[]){
	
	numero_entradas = argc;
	IP_Servidor = argv[1];
	servidorPorta = atoi(argv[2]);
	fprintf(stderr, "IP: %s, Servidor: %d\n",IP_Servidor,servidorPorta);


	gtk_init(&argc, &argv);
	GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	//GtkWidget *btn = gtk_button_new_with_label("Close window");
	//g_signal_connect(btn, "clicked", G_CALLBACK(end_program), NULL);
	//g_signal_connect(win, "delete_event", G_CALLBACK(end_program), NULL);
	GtkWidget *lbl_usuario = gtk_label_new("Usuario: ");
	GtkWidget *lbl_senha = gtk_label_new("Senha: ");

	GtkWidget *lbl_msg = gtk_label_new("Olá! Entre com seu login e senha...");

	GtkWidget *btn_login = gtk_button_new_with_label("Login");
	g_signal_connect(btn_login, "clicked", G_CALLBACK(login), lbl_msg);
	// Criar um campo para inserção de texto
	txt_usuario = gtk_entry_new();
	txt_senha = gtk_entry_new();

	GtkWidget *tab = gtk_table_new(4, 3, TRUE);
	gtk_table_attach_defaults(GTK_TABLE(tab), lbl_usuario, 0, 1, 0, 1);
	gtk_table_attach_defaults(GTK_TABLE(tab), lbl_senha, 0, 1, 0, 2);
	gtk_table_attach_defaults(GTK_TABLE(tab), lbl_msg, 0, 2, 2, 3);


	gtk_table_attach_defaults(GTK_TABLE(tab), btn_login, 1, 2, 3, 4);
	gtk_table_attach_defaults(GTK_TABLE(tab), txt_usuario, 1, 2, 0, 1);
	gtk_table_attach_defaults(GTK_TABLE(tab), txt_senha, 1, 2, 1, 2);

	gtk_container_add(GTK_CONTAINER(win), tab);
	gtk_widget_show_all(win);
	gtk_main();

	

	return 0;
}

int login(GtkWidget *wid, gpointer ptr){
	int socket_id;
	struct sockaddr_in servidorAddr;
	int length;
	//unsigned short servidorPorta;
	//char *IP_Servidor;
	char *mensagem;
	int resposta;
	time_t time_1, time_2;
	char palavra_buffer[100];

	const int creditos_minimos = 5;
	struct usuario usuario_corrente;
	int polegarAutenticado;

	if (numero_entradas < 3){
		printf("Escolha uma opcao valida.\n");
		printf("Para utilizar o programa escreva no terminal:\n./cliente_terminal <IP do Servidor> <Porta do servidor> <nome do usuario> <senha do usuario>\n");
		return -1;
	}

	strcpy(usuario_corrente.nome, gtk_entry_get_text(GTK_ENTRY(entrada_usuario)));
	strcpy(usuario_corrente.senha, gtk_entry_get_text(GTK_ENTRY(entrada_senha)));

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
		fprintf(stderr, "IP: %s, Servidor: %d\n",IP_Servidor,servidorPorta);
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
		sprintf(palavra_buffer,"ID: %d, usuario: %s, senha:%s, creditos:%d\n",
			usuario_corrente.id, usuario_corrente.nome, usuario_corrente.senha, usuario_corrente.creditos);
			printf("%s\n", palavra_buffer);
				gtk_label_set_text(GTK_LABEL(ptr), palavra_buffer);

			//g_signal_connect(btn2, "clicked", G_CALLBACK(copy_text), lbl);

		//abreTranca();	
		//polegarAutenticado = recolheDigital()/256;
		//	printf("Resposta: %d\n", polegarAutenticado);

		if(polegarAutenticado == 10) {
				//abreTranca();
				printf("Abre-te Sesamo!\n");
			}
							time_1 = time(NULL);

		/*while(1){
			time_2 = time(NULL);
			printf("Creditos restantes: %d\n", usuario_corrente.creditos--);
			printf("Tempo de uso do guarda volumes: %4.0f s\n", difftime(time_2, time_1));
			sleep(TEMPO_CREDITOS);
		}*/
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

/*int abreTranca(void){
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
*/
