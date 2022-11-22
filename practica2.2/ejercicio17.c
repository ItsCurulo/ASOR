#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char** argv){
	
	if(argc < 2){
		printf("ERROR: Missing arguments\n");
		exit(1);
	}
	
	DIR* dir = opendir(argv[1]);
	if(dir == NULL){
		printf("ERROR: Can not open directory\n");
		exit(1);
	}
	
	struct dirent* e;
	struct stat e_info;
	off_t size = 0;
	size_t path_length;
	char* path;
	
	while((e = readdir(dir)) != NULL){
		path_length = sizeof(char) * (strlen(argv[1]) + strlen(e->d_name)+ 3);
		path = (char *) malloc(path_length);
		sprintf(path, "%s/%s", argv[1], e->d_name);
		
		if(stat(path, &e_info) == -1){
			printf("ERROR: Can not read a directory entry\n");
			closedir(dir);
			exit(1);		
	
		}
		
		if(e->d_type == DT_REG){
			printf("Regular File: %s", e->d_name);
			
			if((e_info.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)) > 0){
				printf("*\n");
			}
			else printf("\n");
			
			size += e_info.st_size;
			
		}
		else if(e->d_type == DT_DIR){
			printf("Directory: %s\n", e->d_name);
		}
		else if(e->d_type == DT_LNK){
			long p_max = pathconf("/", _PC_NAME_MAX);
			
			char* link = (char*) malloc(p_max + 1);
			readlink(path, link, p_max + 1);
			
			printf("Link: %s -> %s\n", e->d_name, link);	
		}
		
		free(path);
	}	
	
	closedir(dir);
	
	float total_kb = size / 1000;
	printf("Total Regular Files size: %.2f kilobytes\n", total_kb);
	
	return 0;
}
