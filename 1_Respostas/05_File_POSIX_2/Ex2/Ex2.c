#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, const char * argv[])
{
    int fp;
    char nome[100], nome_file[100],idade[3];
    int i;

    printf("Digite seu nome: ");
    scanf("%s", nome);
    printf("Digite sua idade: ");
    scanf("%s", idade);
    strcpy(nome_file,nome);
    strcat(nome_file,".txt");

    fp = open(nome_file,O_WRONLY | O_CREAT, S_IRWXU);
    if(fp == -1){
        printf("Erro ao abrir o arquivo!");
        exit(EXIT_FAILURE);
    }
    write(fp,"Nome: ",6);
    for(i=0 ; nome[i] ; i++) {write(fp,&nome[i],1);}
    write(fp,"\n",1);
    write(fp,"Idade: ",7);
    for(i=0 ; idade[i] ; i++) {write(fp,&idade[i],1);}
	write(fp,"\n",1);
    close(fp);
    return 0;
}
