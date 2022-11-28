#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(){
	sigset_t s;
	sigemptyset(&s);
	sigaddset(&s,SIGINT);
	sigaddset(&s,SIGTSTP);
	char* sleepf=getenv("SLEEP_SECS");
	if(sleepf==NULL){
		printf("ERROR in getenv\n");
		exit(1);
	}
	
	sigprocmask(SIG_BLOCK,&s,NULL);
	sleep(atoi(sleepf));
	sigset_t p;
	int err=sigpending(&p);
	if(err==-1){
		perror("ERROR in sigpending");
		exit(1);
	}
	if(sigismember(&p,SIGINT)){
		printf("SIGINT received\n");
	}
	if(sigismember(&p,SIGTSTP)){
		printf("SIGTSTP received\n");
		sigset_t unloblock_set;
		sigemptyset(&unloblock_set);
		sigaddset(&unloblock_set, SIGTSTP);
		sigprocmask(SIG_UNBLOCK,&unloblock_set,NULL);
	}
	printf("The end\n");
	return 0;
}
