/**
Cuyler Quint
CPS 470
Lab 7
	
	Get familiar with the mapping of a logical address to its page number and offset within the page.

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int virtual_size, m , n, page_size;

void addressAccess(int addresses [], int size)
{
	int address,offset,addressMask,offserMask,page_num;
	printf("   address\t\tpage number\t\toffset\t\tremark"); 
	printf("\n----------------------------------------------------"); 
	for(int j = 0;j < size; j++){
		page_num = addresses[j] / page_size;
		offset = (addresses[j] -(page_num * page_size));
		if(offset < 0)
			printf("\n%d\t\t\t\t\t\t\t invalid",addresses[j]); 
		else
			printf("\n%d(%#6x)\t\t%d(%#6x)\t\t%d(%#6x)",addresses[j],addresses[j],page_num,page_num,offset,offset); 
	
	}
}

int main(int argc, char **argv){
	n = 11;
	m = 6;
	virtual_size = pow(2,n);
	page_size = pow(2,m);
    	int addresses[1000],temp,i= 0;
    	FILE *fp;
    	fp = fopen("data.txt", "r");
	while (fscanf(fp, "%d", &temp) != EOF) {
		addresses[i] = temp;
		i++;
	} 
	addressAccess(&addresses,i);
	return 1;
}
