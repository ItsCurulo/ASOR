#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv){
	if(argc < 2){
		perror("Missing arguments!\n");
		exit(1);
	}
	
	int fd = open("./pipe", O_WRONLY);
	if(fd == -1){
		perror("open");
		exit(1);
	}
	if(write(fd,argv[1],strlen(argv[1]))==-1){
		perror("write");
		exit(1);
	}
	close(fd);
}
