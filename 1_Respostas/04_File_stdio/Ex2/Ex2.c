#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char * argv[])
{
    FILE *fp;
    char nome[100], nome_file[100],idade[3];
    int i;

    printf("Digite seu nome: ");
    scanf("%s", nome);
    printf("Digite sua idade: ");
    scanf("%s", idade);
    strcpy(nome_file,nome);
    strcat(nome_file,".txt");
    printf(nome_file);

    fp = fopen(nome_file,"w");
    if(!fp){
        printf("Erro ao abrir o arquivo!");
        exit(EXIT_FAILURE);
    }
    fputs("Nome: ",fp);
    for(i=0 ; nome[i] ; i++)  putc(nome[i], fp);
    putc('\n', fp);
    fputs("Nome: ",fp);
    for(i=0 ; idade[i] ; i++)  putc(idade[i], fp);
    fclose(fp);
    return 0;
}
