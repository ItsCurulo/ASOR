#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/resource.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#define SOCKET_BACKLOG 5

void handler()
{
		int wstat;
		pid_t	pid;

		while (1) {
			pid = wait3 (&wstat, WNOHANG, (struct rusage *)NULL );
			if (pid == 0 || pid == -1)
				return;
			else
				printf ("Proceso %d - Conexión terminada y recursos liberados\n", pid);
		}
}

void haz_conexion(int client_sd){
	char buf[129];
	ssize_t bytes;

	while(1){
		bytes = recv(client_sd,buf,128,0);
		if(bytes == -1){
			perror("recv");
			exit(1);
		}
		else if(bytes == 0) break;

		if(send(client_sd,buf,strlen(buf),0) == -1){
			perror("send");
			exit(1);
		}

		memset(buf,0,128);
	}
}

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
	hints.ai_protocol=0;

	if(getaddrinfo(argv[1],argv[2],&hints,&res)!= 0){
		perror("getaddrinfo");
		exit(1);
	}

	int sockt = socket(res->ai_family,res->ai_socktype,res->ai_protocol);
	if(sockt == -1){
		perror("socket");
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
	
	int retval;
	struct sockaddr_storage client_addr;
	socklen_t client_addr_len = sizeof(client_addr);
	char host[NI_MAXHOST];
	char service[NI_MAXSERV];
	int client_sd; 
				

	while(1){
		
		if((client_sd = accept(sockt,(struct sockaddr *)&client_addr,&client_addr_len)) == -1){
			perror("accept");
			exit(1);
		}

		retval = getnameinfo((struct sockaddr *)&client_addr,
				     client_addr_len,
				     host,
				     NI_MAXHOST,
				     service,
				     NI_MAXSERV,
				     NI_NUMERICHOST | NI_NUMERICSERV);
		
		if(retval == -1){
			perror("getnameinfo");
			exit(1);
		}
						
		signal (SIGCHLD,handler);
		pid_t pid = fork();
		
		switch(pid){
			case -1:
				return 1;
			case 0:
				close(sockt);
				printf("Proceso %d - Conexión desde %s:%s\n",getpid(),host,service);
				haz_conexion(client_sd);
				return 0;
			default:
				close(client_sd);
				break;
		}
	}
	return 0;
}
