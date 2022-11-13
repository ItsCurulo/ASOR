#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
int main() {
    if(setuid(0)){
    printf("Codigo de error:%i\n",errno);
    printf("Mensaje asociado:%s\n", strerror(errno));
    perror("Error");
 }
 return 1;
}