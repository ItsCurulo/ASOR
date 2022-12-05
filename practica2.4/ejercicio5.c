#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

int main(int argc, char** argv){

	int fd1 = open("./pipe",O_NONBLOCK|O_RDONLY);
	int fd2 = open("./pipe2",O_NONBLOCK|O_RDONLY);
	
	if(fd1==-1 || fd2==-1){
		perror("open");
		exit(1);
	}
	
	fd_set set;
	while(1){
		struct timeval tv;
           	FD_ZERO(&set);
		FD_SET(fd1,&set);
		FD_SET(fd2,&set);
		int max = MAX(fd1,fd2);
		
		int retval = select(max+1,&set,NULL,NULL,NULL);
		
		if(retval == -1)
			perror("select()");
		else{
			if(FD_ISSET(fd1,&set)){
				char buff[256];
				if(read(fd1,buff,256)==0){
					close(fd1);
					fd1=open("./pipe",O_NONBLOCK|O_RDONLY);
				}
				else{
				 	printf("pipe 1 has been written\n");
				 	printf("Content:\n");
				 	printf("%s\n",buff);
				}
			}
			if(FD_ISSET(fd2,&set)){
				char buff[256];
				if(read(fd2,buff,256)==0){
					close(fd2);
					fd2=open("./pipe",O_NONBLOCK|O_RDONLY);
				}
				else{
				 	printf("pipe 2 has been written\n");
					printf("Content:\n");
				  	printf("%s\n",buff);
				}
				
			}
		}	
	}
}
