/**
Cuyler Quint
CPS 450
Act 4
	Implement a basic lexical analyzer for the following tokens	
	(: Open parenthesis
	): Close parenthesis
	‘a’, ‘b’, ‘c’, ‘d’: characters
	‘ ‘: space (ignore)
	“//” : comment (ignore everything after)
	‘+’,’-‘,’*’,’/’: arithmetic operators


	Running:
		./a.out inpt.txt outpt.txt
	
	prints to console and stores results in thrid argument to progarm


*/
#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int i=0,id=0,kw=0,num=0,op=0;


int main(int argc, char **argv){
	char ch;
	char chars[4]= {'a','b','c','d'};
	char opers[4]= {'/','*','-','+'};
	int j;
	fpos_t pos;
	int commented = 0;
	FILE *fi, *fo;
	fi = fopen(argv[1], "r");
	fo = fopen(argv[2], "w+");
	char line[2000];
	int line_c = 0;

	printf("\n\n ---New Tuple---"); 
	fprintf(fo, "\n ---New Tuple---");
	while((ch=fgetc(fi))!=EOF)
	{
		if(commented == 1 && ch =='\n')
		{
			commented = 0;
			continue;
		}
		if(ch=='\n')
		{
			if(fgetc(fi)==EOF)
			{
				printf("\n\nEOF"); 
				fprintf(fo,"\n\nEOF"); 
				exit(1);
			}	
			printf("\n ---New Tuple---"); 
			fprintf(fo, "\n ---New Tuple---");
			continue;
		}
		if(ch=='/')
		{
			char tmp = fgetc(fi);	
			if(tmp=='/')
				printf("\nrest of line has been commeneted");
				printf("\n\n ---New Tuple---"); 
				fprintf(fo, "\\nrest of line has been commeneted\n ---New Tuple---");
				commented = 1;
				continue;				
		}	
		if(ch==' ' || ch=='\0')
			continue;
		for(j=0;j<4;j++)
		{
			
			if(ch==opers[j])
			{
			
				printf("\noperator : %c",ch);
				fprintf(fo, "\noperator : %c",ch);
				op++;
			}
		}
		for(j=0;j<4;j++)
		{
			if(ch==chars[j])
			{
				printf("\nvarible token : %c",ch);
				fprintf(fo, "\nvarible token : %c",ch);
			}
		}
		if(ch=='(')
			printf("\nopen Parenthesis: %c",ch);
			fprintf(fo, "\nopen Parenthesis: %c",ch);
		if(ch==')')
			printf("\nclose Parenthesis: %c",ch);
			fprintf(fo, "\nclose Parenthesis: %c",ch);
	}
}
