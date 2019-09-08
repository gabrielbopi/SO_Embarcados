#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char * argv[])
{
    FILE *fp;
    char nome_file[100];
	int i;
    
    strcpy(nome_file,argv[1]);
    strcat(nome_file,".txt");

    fp = fopen(nome_file,"w");
    if(!fp){
        printf("Erro ao abrir o arquivo!");
        exit(EXIT_FAILURE);
    }
    fputs("Nome: ",fp);
    for(i=0 ; argv[1][i] ; i++)  putc(argv[1][i], fp);
    putc('\n', fp);
    fputs("Nome: ",fp);
    for(i=0 ; argv[2][i] ; i++)  putc(argv[2][i], fp);
	putc('\n', fp);
    fclose(fp);
    return 0;
}
