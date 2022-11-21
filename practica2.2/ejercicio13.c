#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysmacros.h>
#include <time.h>


int main(int argc, char** argv){
	if(argc < 2){
		printf("Error:missing arguments\n");
		exit(1);
	}
	int fdold;
	if(fdold = open(argv[1], O_CREAT | O_RDWR, 0666) == -1){
		perror("open");
		exit(1);
	}

	dup2(fdold, 1);
	dup2(fdold, 2);
	printf("Probando redirección\n");
	fprintf(stderr, "Redireccionando error\n");
	return 0;
}

