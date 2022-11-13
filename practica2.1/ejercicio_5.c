#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>

int main(){
    struct utsname buf;
    if(uname(&buf)){
        perror("Error");
        exit(1);
    }
 printf("Kernel name:%s\n", buf.sysname);
 printf("Nodename:%s\n", buf.nodename);
 printf("Kernel release:%s\n", buf.release);
 printf("Kernel version:%s\n", buf.version);
 printf("Machine:%s\n", buf.machine);
 return 0;
}
