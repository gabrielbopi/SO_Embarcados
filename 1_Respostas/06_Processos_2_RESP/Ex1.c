#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(){
	int i ,pid, pid_pai, child_pid[] = {1,1,1};

	pid_pai = getpid();
	
	for(i=0; (i<=2 & (pid=getpid())==pid_pai) ; i++){		
			child_pid[i] = fork();
	}	
}
