#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <linux/limits.h>

int main(int argc, char** argv){
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
	
	return 0;
}
