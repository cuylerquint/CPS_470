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



int main(int argc, char **argv){


	FILE *fi, *fo;
	fi = fopen(argv[1], "r");
	fo = fopen(argv[2], "w+");
   	Node * root = 0;
	char line[2000];
	int line_c = 0;
	if(fi != NULL)
	{
		while(fgets(line,sizeof line , fi) !=NULL){
			line_c++;
			char * pch;
  			pch = strtok (line," ,?\n");
  			while (pch != NULL)
  			{
    				size_t ln = strlen(pch) - 1;
    				if (*pch  && pch[ln] == '\n') 
					pch[ln] = '\0';
    				if (*pch  && pch[ln-1] == '?') 
    					pch[ln-1] = '\0';
				int *freq = malloc(sizeof *freq);
				freq = insertNode(&root, pch, 0,line_c);
    				pch = strtok (NULL, " ,.-");
  			}	

		}
		fclose(fi);
	}
	print(fo,root);
   	fclose(fo);
	return 0;

}


