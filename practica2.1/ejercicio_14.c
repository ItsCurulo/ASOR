#include <sys/types.h>
#include <unistd.h>
#include<stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    time_t segEpoch=time(NULL);
    if(segEpoch==(time_t)-1){
        perror("Error en funcion time");
        exit(1);
    }
    
    struct tm* time=localtime(&segEpoch);
    printf("Estamos en el año:%i\n",1900+time->tm_year);
    return 0;
}
