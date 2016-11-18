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


//address = address & pagenumber
//pagenumber = (address >> pageBits)
//offset = address & offsetMask



int get_mask(int bits)
{
	int mask = 0;
	for(int i = 0; i <= bits;i++)
		mask = (mask << 1) | 1;
	return mask;
}

void addressAccess(int addresses [], int size)
{
	int address,offset,addressMask,offserMask,page_num;
	printf("   address\t\tpage number\t\toffset\t\tremark"); 
	printf("\n----------------------------------------------------"); 
	for(int j = 0;j < size; j++){
		page_num = addresses[j] / page_size;
	//	address = addresses[j] / page_size;
	//	address = addresses[j] & get_mask(n);
	//	pagenumber = (address >> page_size);
	//	offset = address & get_mask(m);
		offset = (addresses[j] -(page_num * page_size));
	//	printf("\n%d",addresses[j]);
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
    	fp = fopen("data2.txt", "r");
	while (fscanf(fp, "%d", &temp) != EOF) {
		addresses[i] = temp;
		i++;
	} 
	addressAccess(&addresses,i);
	return 1;
}
