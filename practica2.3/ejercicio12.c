#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <linux/limits.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>


volatile int n_INT = 0;
volatile int n_TSTP = 0;

void handlerINT(int value){
	printf("Signal SIGINT\n");
	n_INT++;
}

void handlerSTP(int value){
	printf("Signal SIGTSP\n");
	n_TSTP++;
}

int main(int argc,char** argv){
	struct sigaction actINT;
	actINT.sa_handler = handlerINT;
	struct sigaction actSTP;
	actSTP.sa_handler = handlerSTP;
	sigaction(2,&actINT,NULL);
	sigaction(20, &actSTP,NULL);
	
	while(n_INT + n_TSTP < 10){continue;}
	
	printf("SIGNIT signals:%i, SIGTSTP:%i\n",n_INT,n_TSTP);
	return 0;
}

