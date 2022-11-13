#include <sys/types.h>
#include <unistd.h>
#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

int main(){
    time_t segEpoch=time(NULL);
    if(segEpoch==(time_t)-1){
        perror("Error en funcion time");
        exit(1);
    }
    
    struct tm* time=localtime(&segEpoch);
    char* s;
    setlocale(LC_ALL,"");
    strftime(s,200,"%A,%e de %B de %Y, %R",time);
    printf("%s\n",s);

    return 0;
}