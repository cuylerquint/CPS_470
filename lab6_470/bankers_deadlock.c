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
	int num_proc ,num_res,temp;
	fscanf(fp, "%d,", &num_proc);
	fscanf(fp, "%d,", &num_res);
	int allocation[num_res][num_proc];
	int max[num_res][num_proc];
	int res_avail[num_res];
	int request[num_res][num_proc];
	printf("%d\n",num_proc);
	printf("%d\n",num_res);
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
}
