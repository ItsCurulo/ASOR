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

volatile int suicide = 1;

void handler(int value){
	suicide = 0;
}

int main(int argc,char** argv){
	if(argc < 2){
		printf("ERROR: Missing arguments!\n");
		exit(1);
	}
	struct sigaction act;
	act.sa_handler = handler;
	sigaction(10,&act,NULL);
	sleep(atoi(argv[1]));
	
	if(suicide == 1)unlink(argv[0]);
	else printf("Self destruct aborted\n");
	
	return 0;
}
