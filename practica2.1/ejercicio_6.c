#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    long n;
    if((n=sysconf(_SC_ARG_MAX))==-1){
        perror("Error en ARG_MAX");
        exit(1);
    }
    else printf("ARG_MAX: %li\n",n);
 
    if((n=sysconf(_SC_CHILD_MAX))==-1){
        perror("Error en CHILD_MAX");
        exit(1);
    }
    else printf("CHILD_MAX: %li\n",n);
    
    if((n=sysconf(_SC_OPEN_MAX))==-1){
        perror("Error en OPEN_MAX");
        exit(1);
    }
    else printf("OPEN_MAX: %li\n",n);

    return 0;
}