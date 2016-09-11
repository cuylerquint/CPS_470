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
static int read(FILE *fp);
static void freeTree(Node *root);
static void dumpTree(Node *root);
extern int *insertNode(Node **tree, char *word, int freq, int lines);

int *insertNode(Node **tree, char *word, int freq, int lines)
{
	int c = 0;
	while (word[c])
 	{
		putchar(tolower(word[c]));
      		c++;
  	}
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
	
void read(FILE *fp) {
	int line_num = 1;
	char c;
	int found_word = 0;
	char *cur_word = "";
	while ((c =fgetc(fp)) != EOF )
	{
    		if (!isalpha(c))
    		{	
        		if (found_word) 
			{
            			putchar('\n');
            			found_word = 0;
				printf("word: %s",cur_word);
				
				cur_word = "";
        		}
    		}
    		else 
		{
        		found_word = 1;
        		c = tolower(c);
			size_t len = strlen(cur_word);
			char *str_temp = malloc(len + 1 + 1);
			strcpy(str_temp,cur_word);
			str_temp[len] = c;
			str_temp[len + 1] = '\0';

        		putchar(c);
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
	Node *root = 0;
	read(fi);

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
//		 freq = insertNode(&root, words_temp[i], 0,0);
//		dumpTree(root);
//		printf("New Freq: %d\n", freq);
//	}
	
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

