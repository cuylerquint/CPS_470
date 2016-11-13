/**
Cuyler Quint
CPS 470
Lab 1

	Implement a treemap to print in alphabetical order
	the strings read from a file. In addtion store their
	frequncy and which lines they are located.

	Running:
		./a.out inpt.txt outpt.txt
	
	prints to console and stores results in thrid argument to progarm


*/
#include <stdio.h>

#include <stdlib.h>
#include <string.h>


int main(){
    	FILE *fp;
    	fp = fopen("data.txt", "r");
    	int i, j, executing, num_res, num_proc, temp;
	int count = 0, safe = 0;
	fscanf(fp, "%d,", &num_proc);
	fscanf(fp, "%d,", &num_res);
//	int allocation[num_proc][num_res], max[num_proc][num_res],need[num_proc][num_res], res_avail[num_res], request[num_proc][num_res],finished[num_proc];
	printf("Number of Process:%d\n",num_proc);
	printf("Number of Resouces:%d\n",num_res);

	int allocation[num_proc][num_res];
	int request[num_proc][num_res];
    	int max[num_proc][num_res];
    	int need[num_res];
    	int cur_alloc[num_res];
    	int res_avail[num_res];
    	int running[5];
 

  	for(int i = 0;i < num_proc; i++)
   		running[i]=1;
		count++;                             	
	
	printf("\nallocation matrix:");	
	for(int i = 0; i < num_proc;i++)
	{
		for(int j =0;j< num_res;j++)
		{		
			fscanf(fp, "%d,", &temp);
			allocation[i][j] = temp;
			printf("%d ",allocation[i][j]);
		}
		printf("\n");
	}						
	printf("\nmax matrix:");	
	for(int i = 0; i < num_proc;i++)
	{
		for(int j =0;j< num_res;j++)
		{		
			fscanf(fp, "%d,", &temp);
			max[i][j] = temp;	
			printf("%d ",max[i][j]);
		}
		printf("\n");
	}						

	printf("\nres avil:");	
	for(int j =0;j< num_res;j++)
	{
		fscanf(fp, "%d,", &temp);
		res_avail[j] = temp;
		printf("%d ",res_avail[j]);
	}	

	printf("\nrequest matrix:");	
	for(int i = 0; i < num_proc;i++)
	{
		for(int j =0;j< num_res;j++)
		{		
			fscanf(fp, "%d,", &temp);
			request[i][j] = temp;
			printf("%d ",request[i][j]);
		}
		printf("\n");
	}						
 	for (i = 0; i < num_proc; i++)
        	for (j = 0; j < num_res; j++)
            		cur_alloc[j] += allocation[i][j];	
	printf("\nAllocated: ");
        for (i = 0; i < num_res; i++)
            	printf("%d ", cur_alloc[i]);
	 for(i = 0; i < num_res;i++)
		need[i] = res_avail[i]-cur_alloc[i];				

       	printf("\nAvailble: ");
       	for (i = 0; i < num_res; i++)
        	printf("%d ", need[i]);

	while(count != 0)
	{
		safe = 0;
		for(i = 0;i < num_proc;i++)
		{
			printf("\nRequest %d\t",i + 1);
			for(int j = 0;j < num_res;j++)
				printf("%d ",request[i][j]);

			if(running[i])
			{
				executing = 1;
				for(j = 0; j < num_res;j++)
				{	
					if(max[j][i] - allocation[i][j] > need[j])
					{
						executing = 0;
						printf("Request not granted"); 				
						break;
					}					
				}
				if (executing) {
                    			printf("\nProcess %d is executing.\n", i + 1);
                    			running[i] = 0;
                    			count--;
                    			safe = 1;
                    			for (j = 0; j < num_res; j++)
                        			cur_alloc[j] += allocation[i][j];
                    			break;
                		}
            		}
        	}
 
        	if (safe != 1) {
            		printf("\nDeadlock had occured");
            		break;
        	}
 
        	if (safe)
            		printf("\nSafe state");
 
        	printf("\nAvailble: ");
        		for (i = 0; i < num_res; i++)
            		printf("%d ", res_avail[i]);
		printf("\nAllocated: ");
        		for (i = 0; i < num_res; i++)
            		printf("%d ", cur_alloc[i]);
    	}
 
    return 0;
}
