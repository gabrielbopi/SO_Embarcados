#include <wiringPi.h>
#include <unistd.h>
//#include <stdlib.h>

#define ENTRADA 1
#define ONDA 2

void main(/*int argc, char *argv[]*/){
	pid_t processo_onda;

	wiringPiSetup();
	pinMode(ENTRADA, INPUT);
	pinMode(OUTPUT, OUTPUT);
	pullUpDnControl(ENTRADA, PUD_UP);

	processo_onda = fork();

	if(processo_onda != 0){
		digitalWrite(SAIDA,LOW);
		usleep(PERIODO/2);
		digitalWrite(SAIDA,HIGH);
		usleep(PERIODO/2);
	}
	else{
		for(;;){
			while(digitalRead(ENTRADA) > 0}{}
			kill(processo_onda,SIGUSR1);
			while(!digitalRead(ENTRADA));
			usleep(350000);
		}
	}

	pinMode(ENTRADA, INPUT);
	pinMode(OUTPUT, OUTPUT);
	loop(frequencia);
	
	return 0;
}

void funcao_onda(int frequencia){
	int PERIODO = 1/frequencia;

	while(1){
		digitalWrite(SAIDA,LOW);
		usleep(PERIODO/2);
		digitalWrite(SAIDA,HIGH);
		usleep(PERIODO/2);
	}
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