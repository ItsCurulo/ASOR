#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char** argv){
	if(argc==1){
		printf("Error, arguments missing\n");
		exit(1);
	}
	struct stat statbuf;
	int st;
	if(st = stat(argv[1],&statbuf)==-1){
		perror("stat");
		exit(1);
	}
	if(!S_ISREG(statbuf.st_mode)){
		printf("Error, is not a regular file\n");
		exit(1);
	}
	
	char*c1=malloc(strlen(argv[1])+4);
	char*c2=malloc(strlen(argv[1])+5);
	strcpy(c1,argv[1]);
	strcpy(c2,argv[1]);

	int symlnk;
	if(symlnk=symlink(argv[1],strcat(c1,".sym"))==-1){
		perror("symlink");
		exit(1);
	}
	int hardlnk;
	if(hardlnk=link(argv[1],strcat(c2,".hard"))==-1){
		perror("hardlink");
		exit(1);
	}
	return 0;
}
