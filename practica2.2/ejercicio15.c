#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv){
	if(argc < 2){
		printf("Error: missing arguments\n");
		exit(1);
	}
	int fd;
	if(fd = open(argv[1],O_RDWR) == -1){
		perror("open");
		exit(1);
	}

	int tam = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	int locked = lockf(fd, F_TEST, tam);
	if(locked == 0){
		printf("File not locked\n");
		printf("Locking...\n");
		lockf(fd, F_LOCK, tam);
		time_t t = time(NULL);
		struct tm* date = localtime(&t);
		printf("Current time: %i:%i\n", date->tm_hour, date->tm_min);
		sleep(30);
		lockf(fd, F_ULOCK, tam);
		printf("Unlocking...\n");
	}
	else{
		printf("File locked\n");
	}
	close(fd);
	return 0;
}	
	
	
