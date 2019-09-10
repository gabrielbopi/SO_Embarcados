#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bib_arqs.h"

int main(int argc, char * argv[]) {
	int i, j, ocorrencias = 0, letra_encontrada, tamanho_alvo;
	char *texto, *alvo;
	alvo = argv[1];
	tamanho_alvo = strlen(alvo);
	texto = (char *) malloc(tam_arq_texto(argv[2]));
	texto = le_arq_texto(argv[2]);
	
	for(i=0 ; texto[i] ; i++){
		letra_encontrada = 0;
		if(texto[i] == alvo[0]){
			letra_encontrada++;
			for(j=1 ; j<=tamanho_alvo ; j++){
				if(texto[i+j] == alvo[j])	{letra_encontrada++; }
			}		
		}
		if(letra_encontrada >= tamanho_alvo)	{ocorrencias++;}
	}
	
	printf("'%s' ocorre %d vezes no arquivo '%s'.\n", argv[1], ocorrencias, argv[2]);
}
