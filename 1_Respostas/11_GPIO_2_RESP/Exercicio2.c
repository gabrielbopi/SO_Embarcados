#include <wiringPi.h>
#include <unistd.h>
#include <stdlib.h>

#define INPUT 1
#define ONDA 2

void loop(int frequencia);

void main(int argc, char *argv[]){//Inserir frenquencia em argv[1]
	int frenquencia = atoi(argv[1]);

	wiringPiSetup();
	pinMode(ENTRADA, INPUT);
	pinMode(OUTPUT, OUTPUT);
	loop(frequencia);
	
	return 0;
}

void loop(int frequencia){
	int PERIODO = 1/frequencia;

	while(1){
		digitalWrite(SAIDA,LOW);
		usleep(PERIODO/2);
		digitalWrite(SAIDA,HIGH);
		usleep(PERIODO/2);
	}
}