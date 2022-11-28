#include <sched.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <linux/limits.h>
#include <sys/wait.h>

int main(int argc, char** argv){
	if(argc < 2){
		printf("ERROR: Missing arguments!\n");
		exit(1);
	}
	int err = system(argv[1]);
	if(err == -1){
		printf("Error creating child\n");
		exit(1);
	}
	
	printf("Command execution ended succesfully\n");
	return 0;
}
