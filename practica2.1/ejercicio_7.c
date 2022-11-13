#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    long n;
    if((n=pathconf(".",_PC_LINK_MAX))==-1){
        perror("Error en _LINK_MAX");
        exit(1);
    }
    else printf("_LINK_MAX: %li\n",n);
 
    if((n=pathconf(".",_PC_PATH_MAX))==-1){
        perror("Error en PATH_MAX");
        exit(1);
    }
    else printf("PATH_MAX: %li\n",n);
 
    if((n=pathconf(".",_PC_NAME_MAX))==-1){
        perror("Error en _NAME_MAX");
        exit(1);
    }
    else printf("_NAME_MAX: %li\n",n);
    
    return 0;
}