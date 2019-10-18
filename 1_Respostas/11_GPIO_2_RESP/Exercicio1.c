//1. Escreva um código em C para gerar uma onda quadrada de 1 Hz em um pino GPIO do Raspberry Pi.
#include <wiringPi.h>
#include <unistd.h>


//#define INPUT 1
#define ONDA 2
#define PERIODO 1000

void loop(int frequencia);

void main(){
	wiringPiSetup();
//	pinMode(ENTRADA, INPUT);
	pinMode(OUTPUT, OUTPUT);
	while(1){
		digitalWrite(SAIDA,LOW);
		usleep(PERIODO/2);
		digitalWrite(SAIDA,HIGH);
		usleep(PERIODO/2);
	}
	return 0;
}

/*void loop(int frequencia){

}*/