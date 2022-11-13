#include <sys/types.h>
#include <unistd.h>
#include<stdio.h>

int main(){
    printf("ID real:%i\n",getuid());
    printf("ID efectivo:%i\n",geteuid());
    printf("UID real:%i\n",getgid());
    printf("UID efectivo:%i\n",getegid());
    return 0;
}
