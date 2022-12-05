#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int MAX = 512;

int main(int argc, char* argv[]){
	int p_h[2];
	int h_p[2];
	char buff[MAX];
	if(pipe(p_h) == -1){
		perror("pipe(p_h)");
		exit(1);
	}
	if(pipe(h_p) == -1){
		perror("pipe(h_p");
		exit(1);
	}
	pid_t pid = fork();
	if(pid == -1){
		perror("fork");
		exit(1);
	}
	//Child
	if(pid == 0){
		if(close(p_h[1]) == -1){
			perror("close(p_h[0])");
			exit(1);
		}	
		if(close(h_p[0]) == -1){
			perror("close(h_p[1])");
			exit(1);
		}
		int i = 0;
		while(i < 10){
			if(read(p_h[0],buff,MAX) == -1){
				perror("read(p_h[0]");
				exit(1);
			}
			printf("Message %s seen\n",buff);
			i = i+1;
			if(i< 10){
				strcpy(buff,"l");
				sleep(1);
			}
			else{
				strcpy(buff,"q");
			}
			if(write(h_p[1],buff,strlen(buff) + 1) == -1){		
			perror("write(h_p[0]");
			exit(1);
			}
		}
		if(close(p_h[0]) == -1){
			perror("close(p_h[0])");
			exit(1);
		}
		if(close(h_p[1]) == -1){
			perror("close(h_p[1])");
			exit(1);
		}
		printf("Child finished!\n");
		exit(0);
	} //Parent
	else{
		if(close(p_h[0]) == -1){
			perror("close(h_p[0])");
			exit(1);
		}
		if(close(h_p[1]) == -1){
			perror("close(h_p[1])");
			exit(1);
		}
		int finish = 0;
		while(!finish){
			printf("Enter message: ");
			if(fgets(buff,sizeof(buff),stdin) == NULL){
				perror("fgets");
				exit(1);
			}
			if(write(p_h[1],buff,strlen(buff) + 1) == -1){
			perror("write(p_h[1]");
			exit(1);
			}
			do{
				if(read(h_p[0],buff,MAX) == -1){
					perror("read(h_p[0]");
					exit(1);
				}
			}while(strcmp(buff,"l")!=0 && strcmp(buff,"q")!=0);
			if(strcmp(buff,"q") == 0){
				finish = 1;
			}
		}
		if(close(p_h[1]) == -1){
			perror("close(p_h[1])");
			exit(1);
		}
		if(close(h_p[0]) == -1){
			perror("close(h_p[0])");
			exit(1);
		}
		printf("Parent finished!\n");
		exit(0);
	}
		
}
	





