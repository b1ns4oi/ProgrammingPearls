// implement the order-1 Markov chain

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char s[5000000];
char *a[1000000];
unsigned int num = 0;

//Markov's order
const unsigned int K = 1;

int compare(char **p, char **q)
{
	int n = K;
	char *p1 = *p;
	char *q1 = *q;
	for(; *p1 == *q1; p1++, q1++)
		if(*p1 == 0 && --n ==0)
			return 0;
	return *p1-*q1;
}

// generate random integer in [left, right]
int random_int(int left, int right)
{
	double d = rand()/((double)RAND_MAX + 1);
	double d2 = (right-left+1)*d;
	return (int)d2 + left;
}

int main()
{
	a[0] = s;
	while(scanf("%s", a[num]) != EOF) {
		a[num+1] = &s[strlen(a[num])+1];
		num++;
	}

	int i = 0;
	for(; i < K; i++)
		a[num][i] = 0;

	// sort the suffix array
	qsort(a, num, sizeof(char*), compare);

	//set random seed
	srand((int)time(NULL));

	if(num == 0) return;

	//print the start word
	unsigned int index = random_int(0, num-1);
	char *str = a[index];
	printf("%s", str);

	// binary search the 'str'
	// this version of binary search will find the FIRST candidate if it exists
	int i = -1, j = num;
	while(i+1 != j) {
		int mid = (j-i)/2;
		if(compare(&str, &a[mid]) > 0) i = mid;
		else j = mid; 
	}

	for(i = 0; compare(&str, a[j+i]) == 0; i++)
		if(rand() % (i+1) == 0)
			str = a[j+i];

	// encounter the last word
	if(*(str+strlen(str)+1) == 0)
		return;
	
}