/**
Cuyler Quint
CPS 450
Lab 1

	Implement a raggedness caluator simular to TeX setting
	where Raggedness of a file is calulated by (n - m)**2 sum of lines
	in a text fine. N is the lenght in charaters of longest line.

	Running:
		./a.out inpt.txt 
	
	prints to console 


*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Linked_node {
	int data;
	struct Linked_node * next;
};


typedef struct Linked_node Linked_node;


void push(Linked_node ** head, int val)
{	
	Linked_node * temp = (Linked_node*) malloc(sizeof(Linked_node));
	temp->data = val;
	temp->next = *head;
	*head = temp;
}



int main(int argc, char **argv){
	char ch;
	int cur_char_count = 0,max_char_count = 0, rag = 0;
	FILE *fi;
	fi = fopen(argv[1], "r");
	Linked_node *head = malloc(sizeof(*head));
	head->next = NULL;
	while((ch=fgetc(fi))!=EOF)
	{
		if(ch=='\n')
		{
			push(&head,cur_char_count);
			if(cur_char_count > max_char_count)
			{
				max_char_count = cur_char_count;
			}
			cur_char_count = 0;

		}
		else
		{
			cur_char_count++;
		}
	}
	Linked_node * temp = head;
	while(temp->next != NULL)
	{
		int j = 0;
		if(temp->data ==  max_char_count)
		{
			j = temp->data;
		}
		else
		{
			j = (max_char_count - temp->data);
			j = j*j;

		}
		
		rag += j;
		temp = temp->next;
	}
	printf("\nRaggedness Calc: %d\n", rag);
}
