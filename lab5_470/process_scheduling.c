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
Process pop (Queue* queue);
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
		qsort(jobs, 5, sizeof(Process), sj_compare);
		//queue like sjb, then loop for given qautam
		printf("Round Robin");
	}
 	Queue queue = createQueue();
    	queue.display(&queue);

    	


	for(int j = 0; j < 5; j ++){
		printf("\nPID: %d Arr: %D Burst: %d Pri: %d",jobs[j].pid,jobs[j].arrival,jobs[j].burst,jobs[j].priority);
    		queue.push(&queue, &jobs[j]);    
		jobs[j].execute(&jobs[j],1);
	}
    		queue.display(&queue);
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
