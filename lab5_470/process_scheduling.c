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


int fcfs_compare(const void *s1, const void *s2)
{
	Process *p1 = (Process *)s1;
	Process *p2 = (Process *)s2;
	return p1->arrival - p2->arrival;
}

int sj_compare(const void *s1, const void *s2)
{
	Process *p1 = (Process *)s1;
	Process *p2 = (Process *)s2;
	return p1->burst - p2->burst;
}

//typedef struct Process Process;
void run_process(void *arg)
{
	Process *jobs = arg;
	printf("\nSelect Scheduling Algorithm");
	printf("\n1) FCFS");
	printf("\n2) SJF");
	printf("\n3) RR\n");

	int select;
	scanf("%d",&select);

	if(select == 1)
	{
		qsort(jobs, 5, sizeof(Process), fcfs_compare);

		//sort by arrival
		printf("First Come");
	}
	else if(select == 2)
	{
		qsort(jobs, 5, sizeof(Process), sj_compare);
		//sort by busrt
		printf("Shortest Job First");
	}
	else
	{
		qsort(jobs, 5, sizeof(Process), sj_compare);
		//queue like sjb, then loop for given qautam
		printf("Round Robin");
	}

	for(int j = 0; j < 5; j ++){
		printf("\nPID: %d Arr: %D Burst: %d Pri: %d",jobs[j].pid,jobs[j].arrival,jobs[j].burst,jobs[j].priority);
		jobs[j].execute(&jobs[j],1);
	}

}
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
	pthread_t scheduler;	
	int av_turn_around = 0;
   	pthread_create(&scheduler, NULL, (void *) run_process, (void *) jobs);
    	pthread_join(scheduler, NULL);
	printf("\nFinished Processing Jobs");
	printf("\n Average Turn around time : %d\n",av_turn_around);
}       
