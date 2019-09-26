struct usuario
{
	int id;
	char nome[30], senha[30];
	int creditos; 
};

int adicionaUsuario(char *nome_arquivo, char *nome_usuario,char *senha_usuario);//Retorna id do usuario

struct usuario leUsuario(char *nome_arquivo, char *nome_usuario);//Retorna a struct do usuario


