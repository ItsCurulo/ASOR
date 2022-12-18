#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int main(int argc,char** argv){
	if(argc < 3){
		printf("Missing arguments!\n");
		exit(1);
	}

	struct addrinfo hints;
	struct addrinfo *res;
	memset(&hints,0,sizeof(struct addrinfo));
	
	hints.ai_family=AF_UNSPEC;
	hints.ai_socktype=SOCK_STREAM;
	hints.ai_flags=AI_PASSIVE;

	if(getaddrinfo(argv[1],argv[2],&hints,&res) != 0){
		perror("getaddrinfo");
		exit(1);
	}
	
	int sockt = socket(res->ai_family,res->ai_socktype,res->ai_protocol);
	if(sockt == -1){
		perror("socket");
		exit(1);
	}
	
	if(connect(sockt,res->ai_addr,res->ai_addrlen) == -1){
		perror("connect");
		exit(1);
	}

	while(1){
		char msg[128];
		fgets(msg,128,stdin);
		msg[strlen(msg)-1]='\0';


		if(strcmp(msg,"Q") != 0){
			char buf[128];

			if(send(sockt,msg,sizeof(msg),0) == -1){
				perror("send");
				exit(1);
			}

			ssize_t bytes = recv(sockt,buf,128,0);
			if(bytes == -1){
				perror("recv");
				exit(1);		
			}
			
			buf[bytes] = '\0';
			printf("%s\n",buf);
		}
		else{
			close(sockt);
			exit(0);
		}
	}
	exit(0);
}
