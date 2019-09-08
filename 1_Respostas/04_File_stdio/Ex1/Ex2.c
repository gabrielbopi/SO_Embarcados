#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[]){
    FILE *fp;
    char nome[100];
    int i, idade;
    fp = fopen("ola_mundo.txt","w");
    if(!fp){
        printf("Erro ao abrir o arquivo!");
        exit(EXIT_FAILURE);
    }
    printf("Digite seu nome: ");
    scanf("%s", nome);
    printf("Digite sua idade: ");
    scanf("%d", &idade);
    fputs("Nome: ",fp);
    //for(i=0 ; mensagem[i] ; i++)  putc(mensagem[i], fp);
    //putc('\n', fp);
    fclose(fp);
    return 0;
}
