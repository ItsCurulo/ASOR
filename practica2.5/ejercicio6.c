#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

#define SOCKET_BACKLOG 5

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

	if(getaddrinfo(argv[1],argv[2],&hints,&res)!=0){
		perror("getaddrinfo");
		exit(1);
	}	

	int sockt = socket(res->ai_family,res->ai_socktype,res->ai_protocol);
	if(sockt == -1){
		perror("sockt");
		exit(1);
	}

	if(bind(sockt,res->ai_addr,res->ai_addrlen) == -1){
		perror("bind");
		exit(1);
	}

	freeaddrinfo(res);

	if(listen(sockt,SOCKET_BACKLOG) == -1){
		perror("listen");
		exit(1);
	}

	struct sockaddr_storage client_addr;
	socklen_t client_addr_len = sizeof(client_addr);
	char host[NI_MAXHOST];
	char service[NI_MAXSERV];
	char buf[3];
	int retval;
	int sockfd;
	ssize_t bytes;
	
	while(1){
		sockfd = accept(sockt,(struct sockaddr *) &client_addr, &client_addr_len);
		if(sockfd == -1){
			perror("accept");
			exit(1);
		}

		retval = getnameinfo((struct sockaddr*)&client_addr,
				     client_addr_len,
				     host,
				     NI_MAXHOST,
				     service,
				     NI_MAXSERV,
				     NI_NUMERICHOST | NI_NUMERICSERV);
		if(retval != 0){
			perror("getnameinfo");
			exit(1);
		}

		printf("Conexión desde %s:%s\n",host,service);

		while(1){
			bytes = recv(sockfd,buf,2,0);
			if(bytes == -1){
				perror("recv");
				exit(1);
			}
			else if(bytes == 0) break;
			
			if(send(sockfd,buf,strlen(buf),0) == -1){
				perror("send");
				exit(1);
			}
			
			memset(buf,0,2);	
		}
		close(sockfd);
		printf("Conexión terminada\n");	
	}
	close(sockt);
	return 0;	
}
