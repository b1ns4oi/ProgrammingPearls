// Longest Duplicated String 
// solution using suffix array

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NMAX 100

int compare(const void *p, const void *q)
{
	const char **pp = (const char **)p;
	const char **qq = (const char **)q;
	return strcmp(*pp, *qq);
}

unsigned int comlen(char *p, char *q)
{
	unsigned int ret = 0;
	while(*p && *p++ == *q++)
		ret++;
	return ret;
}

int main()
{
	char s[NMAX];
	scanf("%s", s);

	//build suffix array
	char* suf_array[strlen(s)];
	int i;
	for(i = 0; i < strlen(s); i++)
		suf_array[i] = &s[i];

	//sort suffix array
	qsort(suf_array, strlen(s), sizeof(char*), compare);



	//find the longest duplicate substring
	unsigned int len = 0;
	int index = -1;
	for(i = 0; i < strlen(s) - 1; i++)
		if(comlen(suf_array[i], suf_array[i+1]) > len) {
			len = comlen(suf_array[i], suf_array[i+1]);
			index = i;
		}
	
	//print
	if(len > 0) {
		printf("%.*s\n", len, suf_array[index]);	
	}
	else
		printf("len is less than 0 === %d\n", len);
	
}