#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	int i ,pid, child_pid[] = {1,1,1};
	pid_t pid_filho;
	pid_pai = getpid();
	
	for(i=0; *argv[i] != NULL ; i++){		
		child_pid[i] = fork();
	}	
}
