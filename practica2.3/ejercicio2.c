#include <sched.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv){
	int sch = sched_getscheduler(0);
	if(sch == -1){
		perror("Error: failed to get scheduler policy\n");
		exit(1);
	}
	if(sch == SCHED_OTHER)
		printf("Standart policy: SCHED_OTHER\n");
	else if(sch == SCHED_FIFO)
		printf("FIFO policy: SCHED_FIFO\n");
	else if(sch == SCHED_RR)
		printf("ROUND ROBIN policy; SCHED_RR\n");
		
	struct sched_param param;
	int err = sched_getparam(0,&param);
	if(err == -1){
		perror("ERROR: failed to get sched_getparam\n");
		exit(1);
	}
	
	printf("Priority: %i\n", param.sched_priority);
	printf("Maximum value:%i, Minimum value:%i\n", sched_get_priority_max(sch), sched_get_priority_min(sch));
	return 0;
}
