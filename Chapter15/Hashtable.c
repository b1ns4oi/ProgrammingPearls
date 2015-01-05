
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
	struct node *next;
	char *word;
	unsigned int n;
}node;

#define MAXN 1001
#define MAXWORD 50
#define MULTIPLIER 31

unsigned int hash(char *p)
{
	unsigned int ret = 0;
	for(; *p != '\0'; p++)
		ret = ret*MULTIPLIER + *p;
	return ret % MAXN;
}

void incre_array(node **array, char *word)
{
	unsigned int index = hash(word);
	node *p;
	for(p = array[index]; p != NULL; p = p->next) {
		if(strcmp(p->word, word) == 0) {
			p->n++;
			return;
		}	
	}
	node *nodenew = malloc(sizeof(node));
	nodenew->n = 1;
	nodenew->word = malloc(strlen(word) + 1);
	strcpy(nodenew->word, word);
	nodenew->next = array[index];
	array[index] = nodenew;
}

int main()
{
	node* array[MAXN];
	int i, j, k;
	node *p;
	char word[MAXWORD];
	unsigned int maxlen = 0;

	for(i = 0; i < MAXN; i++)
		array[i] = 0;

	while (scanf("%s", word) != EOF) {
		if(strlen(word) > maxlen)
			maxlen = strlen(word);
		incre_array(array, word);
	}

	for(i = 0; i < MAXN; i++) {
		for(p = array[i]; p != NULL; p = p->next) {
			printf("%s", p->word);
			for(k = 0; k < maxlen-strlen(p->word); k++)
				putchar(' ');
			printf("\t%d\n", p->n);
		}
	}
}