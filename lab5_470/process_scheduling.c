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


typedef struct thread {   
	pthread_t thread_id;       
 	int pid;
	int arrival;
	int burst;
	int priority;
}Process;


int main(){
    FILE *fp;
    int scanned = 0;
    int some_ints[5];
    fp = fopen("data.txt", "r");
    while ((scanned = fscanf(fp, "%d %d %d %d", some_ints, some_ints+1, some_ints+2, some_ints+3)) !=  EOF) {
        if(scanned ==4){
            printf("%d %d %d %d\n", some_ints[0], some_ints[1], some_ints[2], some_ints[3]);
        }
        else {
            printf("Whoops! Input format is incorrect!\n");
            break;
        }
    } 
}       
