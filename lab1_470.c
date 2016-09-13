#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
struct Node{
	struct Node *left, *right;
	int freq, lines;
	char *key;
};

typedef struct Node Node;
static void read(Node * tree,FILE *fp);
static void freeTree(Node *root);
static void dumpTree(Node *root);
static void print(Node *root);
extern int *insertNode(Node **tree, char *word, int freq, int lines);

int *insertNode(Node **tree, char *word, int freq, int lines)
{
//	printf("TOPKEY:   WORD: %s ",word);
	int c = 0;
//	while (word[c])
// 	{
//		putchar(tolower(word[c]));
//      		c++;
//  	}
	if(*tree == NULL)
	{
		Node *tmp = malloc(sizeof(*tmp));
		tmp->key = strdup(word);
		tmp->freq = 1;
		tmp->lines = lines;
		tmp->left = NULL;
		tmp->right = NULL;
		*tree = tmp;
		return tmp->freq;
	}
	else
	{
		Node *temp_tree = *tree;
		printf("\nKEY: %s  WORD: %s ",temp_tree->key,word);
		int r = strcmp(temp_tree->key,word);
		if (r ==0)
		{
			
//			free(temp_tree->freq);
			temp_tree->freq +=1;
			return temp_tree->freq;
		}
		else if(r < 0)
		{
			return insertNode(&temp_tree->right,word,freq,lines);
		}
		else
		{
			return insertNode(&temp_tree->left,word,freq,lines);
		}
	}
}

int stringtoken (Node * tree, char str[], int line)
{
	if(tree == NULL){printf("NULL TREE");}
  	char * pch;
  	pch = strtok (str," ,\n");
  	while (pch != NULL)
  	{
    		size_t ln = strlen(pch) - 1;
    		if (*pch  && pch[ln] == '\n') 
    			pch[ln] = '\0';
    		printf("\nsting: %s line: %d",pch,line); 
		int *freq = malloc(sizeof *freq);
		freq = insertNode(&tree, pch, 0,line);
		printf("New Freq: %d\n", freq);
		dumpTree(tree);
    		pch = strtok (NULL, " ,.-");
  	}
  	return 0;
}

void read(Node *tree,FILE *f1){
	char line[2000];
	int i = 0;
	if(f1 != NULL)
	{
		while(fgets(line,sizeof line , f1) !=NULL){
			i++;
			stringtoken(tree,line,i);
		}
	fclose(f1);
	}
}
		
int main(){
	FILE *fi, *fo;
   	fo = fopen("/Users/cuyler/cps450_470/lab1_470_output.txt", "w+");
   	fi = fopen("/Users/cuyler/cps450_470/temp_inpt.txt", "r");
   	fprintf(fo, "This is testing for fprintf...\n");
   	fputs("This is testing for fputs...\n", fo);
   	fclose(fo);
	Node * root = 0;
	read(root,fi);
	dumpTree(root);
	print(root);
//	Node * root = 0;
//	char *words_temp[]=
//	{
//		{"cat"},	
//		{"dog"},
//		{"pizza"},
//		{"cat"},
//	};
//
//	for(size_t i = 0; i < sizeof(words_temp) / sizeof(words_temp[0]);i++)
//	{
//		printf("%zu: Add %s =>", i, words_temp[i]);
//		int *freq = malloc(sizeof *freq);
//		freq = insertNode(&root, words_temp[i], 0,0);
//		dumpTree(root);
//		printf("New Freq: %d\n", freq);
//	}
//	print(root);	
//	freeTree(root);

	return 0;

}


static void print(Node *root)
{
	printf("HEHEHE");
	if(root != NULL)
	{
		print(root->left);
		printf("%s ... freq: %d, lines: %d\n",root->key,root->freq,root->lines);
		print(root->right);
	}
}

static void freeTree(Node *root)
{
    if (root != 0)
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root->key);
        free(root->freq);
        free(root->lines);
        free(root);
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

