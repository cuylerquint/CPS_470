/*
 * Cuyler Quint
 * Lab 8
 * 12/4/16
 *
 *    Implement a VM Manager to calcuate the localitons of logical and phyicasl address on the page table. 
 *    Then allocate a frame if availble, or use the LRU policy to select the proper frame needed to replace.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int addressBits, pageBits;
int addressMask, pageMask;
int memorySize;

void initialization();
void printSizes();
void processAddresses(char *fname);
int  getMask(int bits);
void displayHeader();
void addressAccess(int address);

int main() {
	initialization();
	printSizes();
    processAddresses("data.txt");
}

int getMask(int bits) {
	int mask = 0;
	int i;
	for (i = 0; i < bits; i++)
		mask = (mask << 1) | 1;
	return mask;
}

void initialization() {
    addressBits = 11;
    pageBits = 6;

    memorySize = pow(2, addressBits);

    addressMask = getMask(addressBits);
    pageMask = getMask(pageBits);
}

void displayHeader() {
	int i;
	printf("\n%10s%10s%10s%10s%10s%10s%10s\n", "log addr", "page #", "offset","clock","frame","phy addr", "remark");
	for (i = 0; i < 70; i++)
		printf("-");
	printf("\n");
}

void printSizes(){
	int pageSize = pow(2, pageBits);
	int numOfPages = memorySize / pageSize;
	printf("%34s%4d\n", "Size of logical address space: ", memorySize);
	printf("%34s%4d\n", "Number of pages in address space: ", numOfPages);
	printf("%34s%4d\n", "Size of a page: ", pageSize);

    displayHeader();
}

void addressAccess(int log_addr) {
	if (log_addr >= memorySize) {
	    printf("%5d%51s\n", log_addr, "Invalid");
	    return;
	}
	static int clock = 0;
	clock++;
	int pageNumber, offset,frame = 111,phy_addr = 111;
	log_addr = log_addr & addressMask;
	pageNumber = log_addr >> pageBits;
	offset = log_addr & pageMask;
	printf("%5d \t\t%3d \t%3d \t%7d \t%3d %5d \n",
			log_addr, pageNumber,offset, clock, frame, phy_addr);
}

void processAddresses(char *fname) {
	FILE* file = fopen (fname, "r");
	int address;
	fscanf (file, "%d", &address);
	while (!feof (file)) {
		addressAccess(address);
		fscanf (file, "%d", &address);
	}
	fclose (file);
}

