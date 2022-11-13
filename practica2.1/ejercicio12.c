#include <sys/types.h>
#include <unistd.h>
#include<stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    time_t t=time(NULL);
    if(t==(time_t)-1){
        perror("Error en time");
        exit(1);
    }
 
    printf("Tiempo en segundos desde Epoch:%li\n",t);
    return 0;
}
