#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(){
    for(int i=0;i<255;i++){
        printf("Error%i:%s\n",i, strerror(i));
    }
 return 1;
}