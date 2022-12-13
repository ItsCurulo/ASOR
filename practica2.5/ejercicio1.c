#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv){
	if(argc < 2){
		printf("Missing arguments!\n");
		exit(1);
	}

	struct addrinfo hints;
	struct addrinfo* res;
	memset(&hints,0,sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;

	if(getaddrinfo(argv[1],NULL,&hints,&res)!=0){
		perror("getaddrinfo");
		exit(1);
	}

	char host[NI_MAXHOST];
	char serv[NI_MAXSERV];
	for(struct addrinfo* ptr=res;ptr != NULL;ptr=ptr->ai_next){
		if(getnameinfo(ptr->ai_addr,ptr->ai_addrlen,host,NI_MAXHOST,NULL,0,NI_NUMERICHOST)!=0){
			perror("getnameinfo");
			exit(1);
		}
		printf("%s %i %i\n",host,ptr->ai_family,ptr->ai_socktype);
	}
	return 0;
}
