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


void keyw(char *p);
int i=0,id=0,kw=0,num=0,op=0;
char keys[32][10]={"auto","break","case","char","const","continue","default",
"do","double","else","enum","extern","float","for","goto",
"if","int","long","register","return","short","signed",
"sizeof","static","struct","switch","typedef","union",
"unsigned","void","volatile","while"};


int main(int argc, char **argv){
	char ch,str[25],seps[15]=" \t\n,;(){}[]#\"<>",oper[]="!%^&*-+=~|.<>/?";
	int j;
	char fname[50];

	FILE *fi, *fo;
	fi = fopen(argv[1], "r");
	fo = fopen(argv[2], "w+");
	char line[2000];
	int line_c = 0;

	while((ch=fgetc(fi))!=EOF)
	{
		for(j=0;j<=14;j++)
		{
			if(ch==oper[j])
			{
				printf("%c is an operator\n",ch);
				op++;
				str[i]='\0';
				keyw(str);
			}
		}
		for(j=0;j<=14;j++)
		{
			if(i==-1)
				break;
			if(ch==seps[j])
			{
				if(ch=='#')
				{
					while(ch!='>')
					{
						printf("%c",ch);
						ch=fgetc(fi);
					}
					printf("%c is a header file\n",ch);
					i=-1;
					break;
				}
				if(ch=='"')
				{
					do
					{
						ch=fgetc(fi);
						printf("%c",ch);
					}while(ch!='"');
					printf("\b is an argument\n");
					i=-1;
					break;
				}
				str[i]='\0';
				keyw(str);
			}
		}
		if(i!=-1)
		{
			str[i]=ch;
			i++;
		}		
		else
			i=0;
	}
	printf("Keywords: %d\nIdentifiers: %d\nOperators: %d\nNumbers: %d\n",kw,id,op,num);
//getch();
}
void keyw(char *p)
{
	int k,flag=0;
	for(k=0;k<=31;k++)
	{
		if(strcmp(keys[k],p)==0)
		{
			printf("%s is a keyword\n",p);
			kw++;
			flag=1;
			break;
		}
	}
	if(flag==0)
	{
		if(isdigit(p[0]))
		{
			printf("%s is a number\n",p);
			num++;
		}
		else
		{
			//if(p[0]!=13&&p[0]!=10)
			if(p[0]!='\0')
			{
				printf("%s is an identifier\n",p);
				id++;
			}
		}
	}
	i=-1;
}
