// problem 9
// Given two input texts, find the longest string that occurs in both

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char s1[100];
char s2[100];
char *a[200]; // suffix array

int compare(char **p, char **q)
{
	return strcmp(*p, *q);
}

int ptr_to_str(char *p, char *str, int n)
{
	return p >= str && p < (str+n);
}

int comlen(char *p, char *q)
{
	int len = 0;
	for(; *p && *p == *q; p++, q++)
		len++;
	return len;
}

// checks if p and q point to different array
int p_xor(char *p, char *q)
{
	return (ptr_to_str(p, s1, strlen(s1)) && ptr_to_str(q, s2, strlen(s2))) ||
	(ptr_to_str(p, s2, strlen(s2)) && ptr_to_str(q, s1, strlen(s1)));
}

int main()
{
	int i, j, maxlen = 0, ns1, ns2;
	char *p;

	// read the string into s1 and s2
	gets(s1);
	gets(s2);
	ns1 = strlen(s1);
	ns2 = strlen(s2);

	// build suffix array
	for(i = 0; i < ns1; i++)
		a[i] = &s1[i];
	for(j = 0; j < ns2; j++)
		a[i+j] = &s2[j];

	// sort
	qsort(a, ns1+ns2, sizeof(a[0]), compare);

	// find the result
	for(i = 0; i < ns1+ns2-1; i++) {
		if(p_xor(a[i], a[i+1]) && comlen(a[i], a[i+1]) > maxlen) {
			maxlen = comlen(a[i], a[i+1]);
			p = a[i];
		}
	}

	// print
	printf("maxlen = %d\n", maxlen);
	printf("%.*s\n", maxlen, p);


}















