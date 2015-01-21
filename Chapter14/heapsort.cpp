// implement 2 versions of heapsort
#include <iostream>
#include <iterator>
#include <algorithm>
#include "PriorityQueue.h"

using std::endl;
using std::cout;
using std::copy;
using std::ostream_iterator;

template<class T>
int less(const T& t1, const T& t2)
{
	return t1 <= t2; 	// class T must overload '<=' properly 
}

template<class T>
void swap(T *a, int i, int j)
{
	T tmp = a[i];
	a[i] = a[j];
	a[j] = tmp;
}

// in-place heap sort
template<class T>
void heapsort_inplace(T *a, int n) // assume element are in a[1]---a[n]
{
	if(n <= 1)
		return;
	//build priority queue
	for(int i = 2; i <= n; ++i) {
		int j = i;
		while(j > 1) {
			if(less(a[j], a[j/2]))
				break;
			swap(a, j, j/2);
			j /= 2;
		}
	}

	//sort
	for(int i = n; i > 1; --i) {
		swap(a, 1, i);
		//siftdown a[1]---a[i-1]
		int r = i-1, j = 1, c;
		while((c = 2*j) <= r) {
			if(c < r && less(a[c], a[c+1]))
				c++;
			if(less(a[c], a[j]))
				break;
			swap(a, c, j);
			j = c;
		}
	}
}

// heap sort using Priority-Queue
template<class T>
void heapsort(T *a, int n) 
{
	if(n <= 1) 
		return;
	PriQueue<T> pq(n);
	int i = n;
	while(i)
		pq.insert(a[--i]);
	while(n--)
		a[i++] = pq.extract_min();
}

int main()
{
	int a[] = {0, 0, 0, 0, 0, 8, 22, 87, 3, 9};
	
	// heapsort_inplace<int>(a, sizeof(a)/sizeof(a[0]) - 1);
	// copy(a+1, a + sizeof(a)/sizeof(a[0]), ostream_iterator<int>(cout, " "));
	// cout << endl;

	heapsort<int>(a, sizeof(a)/sizeof(a[0]));
	copy(a, a + sizeof(a)/sizeof(a[0]), ostream_iterator<int>(cout, " "));
	cout << endl;
}

















