#include <sys/types.h>
#include <unistd.h>
#include<stdio.h>
#include <stdlib.h>
#include <pwd.h>

int main(){
    uid_t id=getuid();
    printf("Usuario ID real:%i\n",id);
    
    struct passwd* pw;
    if((pw=getpwuid(id))==NULL){
        perror("Error getpwuid");
        exit(1);
    }
    
    printf("Nombre de usuario: %s\n",pw->pw_name);
    printf("Home:%s\n",pw->pw_dir);
    printf("Descripcion:$s\n",pw->pw_gecos);
    printf("Id efectivo:%i\n",getuid);
    printf("Id de grupo real:%i\n",getgid());
    printf("Id de grupo efectivo:%i\n",getegid());
    
    return 0;
}
