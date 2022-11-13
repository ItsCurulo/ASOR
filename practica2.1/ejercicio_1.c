#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    if(setuid(0)){
    perror("Error");
 }
 return 1;
}
