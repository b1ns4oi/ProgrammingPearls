// implement the order-1 Markov chain

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char s[5000000];
char *a[1000000];
int num = 0;

//Markov's order
const int K = 1;

int wordncmp(char *p, char *q)
{
	int n = K;
	for(; *p == *q; p++, q++)
		if(*p == 0 && --n == 0)
			return 0;
	return *p - *q;
}

int sortcmp(char **p, char **q)
{	
	return wordncmp(*p, *q);
}

// generate random integer in [left, right]
int random_int(int left, int right)
{
	double d = rand()/((double)RAND_MAX + 1);
	double d2 = (right-left+1)*d;
	return (int)d2 + left;
}

// skip to the next n words from p
char* skip(char *p, int n)
{
	for(; *p || --n > 0; p++)
		;
	return ++p;
}

int main()
{
	a[0] = s;
	while(scanf("%s", a[num]) != EOF) {
		a[num+1] = a[num] + strlen(a[num]) + 1;
		num++;
	}

	int i, j;
	for(i = 0; i < K; i++)
		a[num][i] = 0;

	//print the first K words
	for(i = 0; i < K; i++)
		printf("%s ", a[i]);

	// sort the suffix array
	qsort(a, num, sizeof(char*), sortcmp);

	//set random seed
	srand((int)time(NULL));

	if(num < K) { 
		printf("total words less than K--%d\n", K);
		return;
	}
		
	char *start_ptr = s, *p;
	
	// generate T words most
	int T = 100;
	while(--T > 0) {
		// binary search the 'start_ptr'
		// this version of binary search will find the FIRST candidate if it exists
		i = -1;
		j = num;
		while(i+1 != j) {
			int mid = (j+i)/2;
			if(wordncmp(start_ptr, a[mid]) > 0) i = mid;
			else j = mid; 
		}
		for(i = 0; wordncmp(start_ptr, a[j+i]) == 0; i++)
			if(rand() % (i+1) == 0)
				p = a[j+i];

		// encounter the last word
		if(strlen(skip(p, K)) == 0)
			return;

		// print the candidate word
		printf("%s ", skip(p, K));

		// set 'start_ptr'
		start_ptr = skip(p, 1);
	}
}






