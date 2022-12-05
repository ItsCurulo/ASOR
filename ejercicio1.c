#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
	if(argc < 5){
		printf("Missing arguments!\n");
		exit(1);
	}
	
	int pipefd[2];
	if(pipe(pipefd) == -1){
		perror("pipe");
		exit(1);
	}
	
	int pid = fork();
	if(pid == -1){
		perror("fork");
		exit(1);	
	}
	else if(pid == 0){
		if(dup2(pipefd[0],0) == -1){
			perror("dup2");
			exit(1);
		}
		if(close(pipefd[0]) == -1){
			perror("close");
			exit(1);
		}
		if(close(pipefd[1]) == -1){
			perror("close");
			exit(1);
		}
		execlp(argv[3],argv[3],argv[4],(char*)0);
	}
	else {
		if(dup2(pipefd[1],1) == -1){
			perror("dup2");
			exit(1);
		}
		if(close(pipefd[0]) == -1){
			perror("close");
			exit(1);
		}
		if(close(pipefd[1]) == -1){
			perror("close");
			exit(1);
		}
		execlp(argv[1],argv[1],argv[2],(char*)0);
	}
	exit(1);
}
