#include<sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char**argv){
	if(argc<2){
		printf("Error,arguments missing\n");
		exit(1);
	}

	int oldfd;
	if(oldfd=open(argv[1],O_CREAT|O_RDWR,0666==-1)){
		perror("open");
		exit(1);
	}
	dup2(oldfd,1);
	printf("Testing redirect\n");
	return 0;
}
