#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, const char * argv[])
{
	int fp;
    	char nome_file[100];
	int i;
    
    	strcpy(nome_file,argv[1]);
    	strcat(nome_file,".txt");

	fp = open(nome_file,O_WRONLY | O_CREAT, S_IRWXU);
	if(fp == -1){
        	printf("Erro ao abrir o arquivo!");
        	exit(EXIT_FAILURE);
    	}
    	write(fp,"Nome: ",6);
    	for(i=0 ; argv[1][i] ; i++) {write(fp,&argv[1][i],1);}
    	write(fp,"\n",1);
    	write(fp,"Idade: ",7);
    	for(i=0 ; argv[2][i] ; i++) {write(fp,&argv[2][i],1);}
	write(fp,"\n",1);
    	close(fp);
    	return 0;
}
