#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysmacros.h>
#include <time.h>

int main(int argc, char** argv){
	struct stat statbuf;
	if(argc!=2){
		printf("Warning:missing filename\n");
		exit(1);
	}
	int st;
	if((st = stat(argv[1],&statbuf)) == -1){
		perror("Stat");
		exit(1);
	}
	printf("Major:%i\n", major(statbuf.st_dev));
	printf("Minor:%i\n", minor(statbuf.st_dev));
	printf("Nº de i-nodo:%li\n", statbuf.st_ino);
	
	if(S_ISREG(statbuf.st_mode)){
		printf("Regular file\n");
	}
	else if(S_ISDIR(statbuf.st_mode)){
		printf("Directory\n");
	}
	else if(S_ISLNK(statbuf.st_mode)){
		printf("Symbolic link\n");
	}
	struct tm * time = localtime(&statbuf.st_atime);
	printf("Last access: %i:%i \n", time->tm_hour, time->tm_min);
	
	return 0;
}
