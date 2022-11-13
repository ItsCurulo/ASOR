#include <sys/types.h>
#include <unistd.h>
#include<stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main(){
    struct timeval timeIni;
    if(gettimeofday(&timeIni,NULL)){
        perror("Error en gettimeofday(primera llamada)");
        exit(1);
    }
    
    int v=0;
    for(int i=0;i<1e6;i++){
        v++;
    }
 
    struct timeval timeFin;
    if(gettimeofday(&timeFin,NULL)){
        perror("Error en gettimeofday(segunda llamada)");
        exit(1);
    }
 
    printf("Segundos transcurridos:%li\n",timeFin.tv_sec-timeIni.tv_sec);
    printf("Microsegundos transcurridos:%li\n",timeFin.tv_usec-timeIni.tv_usec);
    return 0;
}