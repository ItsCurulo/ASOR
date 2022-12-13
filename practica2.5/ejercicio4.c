#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netdb.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <sys/select.h>

int main(int argc,char **argv){
	if(argc < 3){
		printf("Missing arguments!\n");
		exit(1);
	}

	struct addrinfo hints;
	struct addrinfo *res;
	memset(&hints,0,sizeof(struct addrinfo));

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE;

	if(getaddrinfo(argv[1],argv[2],&hints,&res) != 0){
		perror("getaddrinfo");
		exit(1);
	}
	
	int sockt = socket(res->ai_family,res->ai_socktype,res->ai_protocol);
	if(sockt == -1){
		perror("socket");
		exit(1);
	}

	if(bind(sockt,res->ai_addr,res->ai_addrlen)==-1){
		perror("bind");
		exit(1);
	}

	freeaddrinfo(res);

	struct sockaddr_storage client_addr;
	socklen_t client_addrlen = sizeof(client_addr);
	char host[NI_MAXHOST];
	char service[NI_MAXSERV];
	char msg[129];
	char buf[3];
	time_t t;
	struct tm *tm;
	size_t size;
	ssize_t bytes;
	int finish = 0;

	fd_set fds;


	do{
		FD_ZERO(&fds);
		FD_SET(0,&fds);
		FD_SET(sockt,&fds);

		if(select(sockt+1,&fds,NULL,NULL,NULL) == -1){
			perror("select");
			exit(1);
		}

		if(FD_ISSET(0,&fds)){
			bytes = read(0,buf,2);
		}
		else{
			bytes = recvfrom(sockt,buf,2,0,(struct sockaddr *) &client_addr, &client_addrlen);
			buf[bytes-1] = '\0';

			getnameinfo((struct sockaddr *) &client_addr, 					     client_addrlen,
				     host,
                                     NI_MAXHOST,
				     service,
				     NI_MAXSERV,
				     NI_NUMERICHOST | NI_NUMERICSERV);
			printf("%ld bytes de %s:%s\n",bytes,host,service);	
		}

		t = time(NULL);
		tm = localtime(&t);

		if(buf[0] == 't'){
			size = strftime(msg,128,"%T",tm);
			msg[size] = '\n';
			msg[size+1] = '\0';
			
			if(FD_ISSET(0,&fds)) printf("%s\n",msg);
			else{
				if(sendto(sockt,msg,size+2,0,(struct sockaddr *) &client_addr, client_addrlen) == -1){
					perror("sendto");
					exit(1);
				}
			}
		}
		else if(buf[0] == 'd'){
			size = strftime(msg,128,"%F",tm);
			msg[size] = '\n';
			msg[size+1] = '\0';

			if(FD_ISSET(0,&fds)) printf("%s\n",msg);
			else{
				if(sendto(sockt,msg,size+2,0,(struct sockaddr *) &client_addr, client_addrlen) == -1){
					perror("sendto");
					exit(1);
				}
			}
		}
		else if(buf[0] == 'q'){
			printf("Saliendo...\n");
			finish = 1;
		}
		else printf("Comando no soportado %s\n", buf);
	}while(!finish);
	
	close(sockt);
	return 0;
}
