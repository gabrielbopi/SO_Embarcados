#include <stdio.h>
#include "num_caracs.h"

int main(int argc, char **argv){
	int i;
	for(i=1 ; i<argc ; i++){
		printf("\nArgumento: ");
		printf(" %s", argv[i]);
		printf("/ Numero de caracteres: ");
		//printf("%d", Num_caracs(argv[i]));
	}
	printf("\n");
	return 0;
}
