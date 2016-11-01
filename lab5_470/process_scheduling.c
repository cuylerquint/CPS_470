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
double ave_turn_around = 0, ave_wait = 0;
typedef struct{   
 	int pid;
	int arrival;
	int burst;
	int priority;
	int comp_time;
	void (*execute)();
}Process;

void execute(Process * self, int quantum)
{
	printf("\nProcess: %d executeing for %d, process has %d time left",self->pid,quantum, self->burst);
	usleep(quantum);	

}



typedef struct Node {
	Process process;
    	struct Node* next;
} Node;

typedef struct Queue {
    	Node* head;
    	Node* tail;

    	void (*push) (struct Queue*, Process*); // add item to tail
    	Process (*pop) (struct Queue*);
    	int (*peek) (struct Queue*);
    	void (*display) (struct Queue*);
    	int size;
} Queue;

void push (Queue* queue, Process * p);
Process  pop (Queue* queue);
int peek (Queue* queue);
void display (Queue* queue);

void push (Queue* queue, Process * p) {
	Node* n = (Node*) malloc (sizeof(Node));
    	n->process = *p;
    	n->next = NULL;

    	if (queue->head == NULL) { // no head
        	queue->head = n;
    	}
	else
	{
        	queue->tail->next = n;
    	}
    	queue->tail = n;
    	queue->size++;
}

Process pop (Queue* queue) {
    	Node* head = queue->head;
    	Process p  = head->process;
    	queue->head = head->next;
    	queue->size--;
    	free(head);
    	return p;
}

int peek (Queue* queue) {
    	Node* head = queue->head;
    	return head->process.pid;
}
void display (Queue* queue) {
    	printf("\nDisplay: ");
    // no item
    	if (queue->size == 0)
        	printf("No item in queue.\n");
    	else { // has item(s)
        	Node* head = queue->head;
        	int i, size = queue->size;
        	printf("%d item(s):\n", queue->size);
        	for (i = 0; i < size; i++) {
            		if (i > 0)
                		printf(", ");
            		printf("%d", head->process.pid);
            		head = head->next;
        	}
    	}
    	printf("\n\n");
}

Queue createQueue () {
	Queue queue;
    	queue.size = 0;
    	queue.head = NULL;
    	queue.tail = NULL;
    	queue.push = &push;
    	queue.pop = &pop;
    	queue.peek = &peek;
    	queue.display = &display;
    	return queue;
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
		qsort(jobs, 5, sizeof(Process), fcfs_compare);
		printf("Round Robin");
	}
 	Queue queue = createQueue();
	int max_burst = 0;
	for(int j = 0; j < 5; j ++){
		printf("\nPushing Process %d Arr: %D Burst: %d Pri: %d",jobs[j].pid,jobs[j].arrival,jobs[j].burst,jobs[j].priority);
		jobs[j].comp_time = 4;
    		queue.push(&queue, &jobs[j]);    
		if(jobs[j].burst > max_burst)
			max_burst = jobs[j].burst;
	}
	// turn around = finished - arrival, wait = turn around - burst	
	int running_clock = 0, comp_time,turn_around, wait;
	if(select == 3) // RR
	{
		int orig_burst;
		while(queue.size != 0)
		{

			Process temp = queue.pop(&queue);
			temp.execute(&temp,10);
			temp.burst -= 10;
			if(temp.burst > 0)
				queue.push(&queue,&temp);
			else
			{
				for(int i = 0; i < 5; i ++){
					if(jobs[i].pid == temp.pid)
						orig_burst = jobs[i].burst;					
				}
				comp_time = running_clock + temp.burst;
				turn_around = comp_time - temp.arrival;
				wait = turn_around - orig_burst;
				ave_turn_around += turn_around;
				ave_wait += wait;
			}			
			
		}			
	}
	else if(select == 2) //shortest
	{
		while(queue.size != 0)
		{
			Process temp = queue.pop(&queue);
			temp.execute(&temp,max_burst);
			comp_time = running_clock + temp.burst;
			turn_around = comp_time - 0;
			wait = turn_around - temp.burst;
			ave_turn_around += turn_around;
			ave_wait += wait;
			printf("\nProcess %d Turn Around: %D Wait: %d",temp.pid,turn_around,wait);	
			running_clock += max_burst;	
		}	
	}
	else
	{
		while(queue.size != 0)
		{
			Process temp = queue.pop(&queue);
			temp.execute(&temp,max_burst);
			comp_time = running_clock + temp.burst;
			turn_around = comp_time - temp.arrival;
			wait = turn_around - temp.burst;
			ave_turn_around += turn_around;
			ave_wait += wait;
			printf("\nProcess %d Turn Around: %D Wait: %d",temp.pid,turn_around,wait);	
			running_clock += max_burst;	

		}	
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
			jobs[i].pid = some_ints[0];
			jobs[i].arrival = some_ints[1];
			jobs[i].burst = some_ints[2];
			jobs[i].priority = some_ints[3];
			jobs[i].execute = &execute;
			i += 1;
        	}
	} 
	pthread_t scheduler;	
	int av_turn_around = 0;
   	pthread_create(&scheduler, NULL, (void *) run_process, (void *) jobs);
    	pthread_join(scheduler, NULL);
	printf("\n\nFinished Processing Jobs\n");
	printf("Average Turn around time : %f\n",(ave_turn_around/i));
	printf("Average Wait time : %f\n",(ave_wait/i));
}       
