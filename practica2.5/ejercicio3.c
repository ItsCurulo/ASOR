#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc,char** argv){
	if(argc < 4){
		printf("Missing arguments!\n");
		exit(1);
	}

	struct addrinfo hints;
	struct addrinfo* res;
	memset(&hints,0,sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE;
	
	if(getaddrinfo(argv[1],argv[2],&hints,&res)!= 0){
		perror("getaddrinfo");
		exit(1);
	} 
	
	int sockt = socket(res->ai_family,res->ai_socktype,res->ai_protocol);
	if(sockt == -1){
		perror("socket");
		exit(1);
	}

	if(sendto(sockt,argv[3],sizeof(argv[3]),0,res->ai_addr,res->ai_addrlen) == -1){
		perror("sendto");
		exit(1);
	}
	
	char buf[128];
	struct sockaddr_storage client_addr;
	socklen_t client_addrlen = sizeof(client_addr);
	 
	if(recvfrom(sockt,buf,128,0,(struct sockaddr *) &client_addr, &client_addrlen) == -1){
		perror("recvfrom");
		exit(1);
	}
	printf("%s\n",buf);
	close(sockt);	
	return 0;	 
}
