#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[]){
    FILE *fp;
    const char mensagem[] = {"Ola mundo!"};
    int i;
    fp = fopen("ola_mundo.txt","w");
    if(!fp){
        printf("Erro ao abrir o arquivo!");
        exit(EXIT_FAILURE);
    }
    for(i=0 ; mensagem[i] ; i++)  putc(mensagem[i], fp);
    putc('\n', fp);
    fclose(fp);
    return 0;
}
