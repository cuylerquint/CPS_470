#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Linked_node {
	int line;
	struct Linked_node * next;
};

struct Node{
	struct Node *left, *right;
	struct Linked_node line_list;
	int freq;
	char *key;
};


typedef struct Linked_node Linked_node;
typedef struct Node Node;
static void read(Node * tree,FILE *fp);
static void dumpTree(Node *root);
static void print(Node *root);
extern int *insertNode(Node **tree, char *word, int freq, int lines);

int *insertNode(Node **tree, char *word, int freq, int line_location)
{
	for(int i = 0; word[i] != '\0';i++)
		word[i] = tolower(word[i]);
	if(strlen(word) == 0)
		return 0;
	if(*tree == NULL)
	{
		Node *tmp = malloc(sizeof(*tmp));
		Linked_node *tmp_list = malloc(sizeof(*tmp_list));
		tmp_list->line = line_location;
		tmp_list->next = NULL;
		tmp->line_list = *tmp_list;
		tmp->key = strdup(word);
		tmp->freq = malloc(sizeof(int));
		tmp->freq = 1;
		tmp->left = NULL;
		tmp->right = NULL;
		*tree = tmp;
		return tmp->freq;
	}
	else
	{
		Node *temp_tree = *tree;
		if(temp_tree == NULL)
			return 0;
		int r = strcmp(temp_tree->key,word);
		if (r ==0)
		{
			temp_tree->freq +=1;
			Linked_node * current = &temp_tree->line_list;
			Linked_node * cur = &temp_tree->line_list;
			int max = 0;
			while(cur != NULL)
			{	
				if(cur->line > max){max = cur->line;}
				cur = cur->next;
			}
			if(max != line_location)
			{
				while(current->next != NULL)
					current = current->next;
				current->next = malloc(sizeof(Linked_node));
				printf("NEW LINE LOCATION IN LINKED:%d", line_location);
				current->next->line = line_location;
				current->next->next = NULL;			
			}			
			return temp_tree->freq;
		}
		else if(r < 0)
		{
			return insertNode(&temp_tree->right,word,freq,line_location);
		}
		else
		{
			return insertNode(&temp_tree->left,word,freq,line_location);
		}
	}
}


		
int main(){
	FILE *fi, *fo;
   	fo = fopen("/Users/cuyler/cps450_470/lab1_470_output.txt", "w+");
   	fi = fopen("/Users/cuyler/cps450_470/lab1_470_input.txt", "r");
   	fprintf(fo, "This is testing for fprintf...\n");
   	fputs("This is testing for fputs...\n", fo);
   	fclose(fo);
	Node * root = 0;
	char line[2000];
	int line_c = 0;
	if(fi != NULL)
	{
		while(fgets(line,sizeof line , fi) !=NULL){
			line_c++;
		//	stringtoken(tree,line,i);
			char * pch;
  			pch = strtok (line," ,?\n");
  			while (pch != NULL)
  			{
    				size_t ln = strlen(pch) - 1;
    				if (*pch  && pch[ln] == '\n') 
					pch[ln] = '\0';
    				if (*pch  && pch[ln-1] == '?') 
    					pch[ln-1] = '\0';
    				printf("\nsting: %s line: %d",pch,line_c); 
				int *freq = malloc(sizeof *freq);
				freq = insertNode(&root, pch, 0,line_c);
				printf("New Freq: %d\n", freq);
				dumpTree(root);
    				pch = strtok (NULL, " ,.-");
  			}	

		}
		fclose(fi);
	}
	print(root);

	return 0;

}


static void print(Node *root)
{
	if(root != NULL)
	{
		print(root->left);
		printf("\n%s\tfreq: %d\tlines: ",root->key,root->freq);
		Linked_node * cur = &root->line_list;
		
		while(cur != NULL)
		{	
			printf("%d ", cur->line);
			cur = cur->next;
		}
		print(root->right);
	}
}

static void dumpTree(Node *root)
{
    if (root->left != 0)
        dumpTree(root->left);
    printf("%p: %s => freq:%d\n", (void *)root, root->key, root->freq);
    if (root->right != 0)
        dumpTree(root->right);
}
