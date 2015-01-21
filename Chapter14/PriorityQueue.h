#ifndef _GUARD_PRIQUEUE_H_
#define _GUARD_PRIQUEUE_H_

#include <iostream>

using std::cout;
using std::endl;

template<class T>
class PriQueue {
public:
    PriQueue(int maxlen = 10) : max(maxlen), n(0) { p = new T[maxlen+1]; }
    ~PriQueue() { delete[] p; }
    void insert(T t);
    T extract_min();
    //for debug
    void print()
    {
        for(int i = 1; i <= n; ++i)
            cout << p[i] << " ";
        cout << endl;
    }
private:
    T *p;
    int max;
    int n;
    void swap(int i, int j) { T tmp = p[i]; p[i] = p[j]; p[j] = tmp; }
};

template<class T>
void PriQueue<T>::insert(T t)
{
    if(n+1 > max) {
        cout << "array is full..." << endl;
        return;
    }
    p[++n] = t;
    // siftup p[n]
    int i = n;
    while(i > 1 && p[i] < p[i/2]) {
        swap(i, i/2);
        i /= 2;
    }
}

template<class T>
T PriQueue<T>::extract_min()
{
    if(n < 1) {
        cout << "no elements in array." << endl;
        return T();
    }
    T ret = p[1];
    p[1] = p[n--];
    //siftdown p[1]
    //pre-invariant: heap(2, n)
    //post-invariant: heap(1, n)
    int par = 1, c;
    while((c = 2*par) <= n) {
        if(c < n && p[c] > p[c+1])
            c++;
        if(p[par] <= p[c])
            break;
        swap(par, c);
        par = c;
    }
    return ret;
}

#endif
