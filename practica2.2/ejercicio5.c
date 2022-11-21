#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
	if(argc==1){
		printf("WARNING:filename missing\n");
		exit(1);
	}
	
	int fd;
	if(fd = open(argv[1], O_CREAT, 0645) == -1){
		perror("Open");
		exit(1);
	}
	return 0;
}
