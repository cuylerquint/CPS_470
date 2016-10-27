/**
Cuyler Quint
CPS 470
Lab 5

	Implement process scheduling via FCFS, SJB, RR

	input: 
	pid	arrival time	burst	priority
	1	2		87	3		

	Running:
		./a.out
	
	prints to console and stores results in thrid argument to progarm


*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct{   
 	int pid;
	int arrival;
	int burst;
	int priority;
	void (*execute)();
}Process;

void execute(Process * self, int quantum)
{
	printf("\nProcess: %d executeing for %d",self->pid,quantum);
	sleep(quantum);	

}

//typedef struct Process Process;

int main(){
    	FILE *fp;
    	int scanned = 0;
    	int some_ints[5];
	Process jobs[5];	
    	fp = fopen("data.txt", "r");
	int i = 0;
	while ((scanned = fscanf(fp, "%d %d %d %d", some_ints, some_ints+1, some_ints+2, some_ints+3)) !=  EOF) {
        	if(scanned ==4){
			printf("%d %d %d %d\n", some_ints[0], some_ints[1], some_ints[2], some_ints[3]);
			jobs[i].pid = some_ints[0];
			jobs[i].arrival = some_ints[1];
			jobs[i].burst = some_ints[2];
			jobs[i].priority = some_ints[3];
			jobs[i].execute = &execute;
			i += 1;
        	}
        	else 
		{
			printf("Whoops! Input format is incorrect!\n");
            		break;
        	}
	} 
	for(int j = 0; j < 5; j ++){
		printf("\nPID: %d Arr: %D Burst: %d Pri: %d",jobs[j].pid,jobs[j].arrival,jobs[j].burst,jobs[j].priority);
		jobs[j].execute(&jobs[j],1);
	}
	
}       
