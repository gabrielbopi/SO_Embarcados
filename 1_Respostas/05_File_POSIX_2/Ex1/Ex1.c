#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, const char * argv[]){
    int fp;
    const char mensagem[] = {"Ola mundo!\n"};
    int i;
    fp = open("ola_mundo.txt",O_WRONLY | O_CREAT, S_IRWXU);
    if(fp == -1){
        printf("Erro ao abrir o arquivo!\n");
        exit(EXIT_FAILURE);
    }
    for(i=0 ; mensagem[i] ; i++)  write(fp, &(mensagem[i]), 1);
    write(fp,"\n", 1);
    close(fp);
    return 0;
}
