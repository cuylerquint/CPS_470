#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
struct Node{
	struct Node *left, *right;
	int *freq, *lines;
	char *key;
};

typedef struct Node Node;

static void freeTree(Node *root);
static void dumpTree(Node *root);
extern int *insertNode(Node **tree, char *word, int *freq, int *lines);

int *insertNode(Node **tree, char *word, int *freq, int *lines)
{
	int c = 0;
	while (word[c])
 	{
		putchar(tolower(word[c]));
      		c++;
  	}
	printf("\nTEMP CHAR:%s",word);
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
		printf("\ntemp_treek: %s word: %s", temp_tree->key,word);
		int r = strcmp(temp_tree->key,word);
		printf("\n%d",r);
		if (r ==0)
		{
			
			free(temp_tree->freq);
			int temp = temp_tree->freq + 1;
			printf("!!!!: %d\n",temp);
			temp_tree->freq = temp_tree->freq + 1;
			
			return temp_tree->freq;
		}
		else if(r < 0)
		{
			printf("\nTEMP LEFT");
			return insertNode(&temp_tree->right,word,freq,lines);
		}
		else
		{
			printf("\nTEMP Right");
			return insertNode(&temp_tree->left,word,freq,lines);
		}
	}
}
			
int main(){
	FILE *fp;
   	fp = fopen("/Users/cuyler/cps450_470/lab1_470_output.txt", "w+");
   	fprintf(fp, "This is testing for fprintf...\n");
   	fputs("This is testing for fputs...\n", fp);
   	fclose(fp);
	
	Node *root = 0;

	char *words_temp[]=
	{
		{"cat"},	
		{"dog"},
		{"pizza"},
		{"Cat"},
	};

	for(size_t i = 0; i < sizeof(words_temp) / sizeof(words_temp[0]);i++)
	{
		printf("%zu: Add %s =>", i, words_temp[i]);
		int *freq = malloc(sizeof *freq);
		 freq = insertNode(&root, words_temp[i], 0,0);
		dumpTree(root);
		printf("New Freq: %d\n", freq);
	}
	
//	freeTree(root);

	return 0;

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

