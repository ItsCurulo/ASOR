#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <linux/limits.h>
void show_info(){
	pid_t pid = getpid();
	int sid = getsid(pid);
	if(sid == -1){
		perror("ERROR: Failed to get SID\n");
		exit(1);
	}
	
	printf("PID:%i,PPID:%i,GPID:%i,SID:%i\n", pid,getppid(),getpgrp(),sid);	
	struct rlimit rlim;
	int err = getrlimit(RLIMIT_NOFILE,&rlim);
	char* buf = malloc(PATH_MAX);
	if(getcwd(buf,PATH_MAX) == NULL){
		perror("Error calling getcwd\n");
		exit(1);
	}
	printf("Work Directory:%s\n", buf);
	free(buf);
	if(err == 1){
		perror("Error calling getrlimit function\n");
		exit(1);
	}
	printf("Maximum files limit. SOFT:%li Hars: %li\n", rlim.rlim_cur,rlim.rlim_max);
}

int main(int argc, char** argv){
	int pid = fork();
	if(pid == -1){
		perror("Error in function fork\n");
		exit(1);
	}
	else if(pid == 0){
		pid_t sesion = setsid();
		if(sesion == -1){
			perror("Error in function setsid\n");
			exit(1);
		}
		int err = chdir("/tmp");
		if(err == -1){
			perror("chdir\n");
			exit(1);
		}
		show_info();
		exit(0);
	}
	else{
		sleep(3);
	}
		
	return 0;
}
