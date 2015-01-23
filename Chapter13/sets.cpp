
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

class IntSetBST{
public:
	IntSetBST(int maxelements, int maxval);
	void insert(int t);
	int size();
	void report(int *v);
private:
	struct node {
		int val;
		node *left;
		node *right;
		node(int v = 0, node *l = 0, node *r = 0): val(v), left(l), right(r) { }
	};
	node *root;
	int n, *v, vn;

	node *rinsert(node *p, int t)
	{
		if(p == 0) {
			p = new node(t, 0, 0);
			n++;
		}
		if(p->val < t) 		p->right = rinsert(p->right, t);
		else if(p->val > t) p->left  = rinsert(p->left, t);
		return p;
	}

	// Buggy !!!
	// void traverse(node *p, int *v)
	// {
	// 	if(p == 0)
	// 		return;
	// 	traverse(p->left, v);
	// 	*v++ = p->val;
	// 	traverse(p->right, v);
	// }
	void traverse(node *p)
	{	if (p == 0)
			return;
		traverse(p->left);
		v[vn++] = p->val;
		traverse(p->right);
	}

};

IntSetBST::IntSetBST(int maxelements, int maxval)
{
	n = 0;
	root = 0;
	//sentinel = new node(maxval, 0, 0);
}

void IntSetBST::insert(int t)
{
	root = rinsert(root, t);
}

void IntSetBST::report(int *x)
{
	v = x; vn = 0; 
	traverse(root);
}

int IntSetBST::size()
{
	return n;
}

// sentinel; one-time memory allocation; recursion removal
class IntSetBST2 {
public:
	IntSetBST2(int maxelements, int maxval) 
	{
		n = 0;
		freenode = new node[maxelements];
		root = sentinel = new node;
	}
	void insert(int t)
	{
		node **p = &root;
		sentinel->val = t;
		while((*p)->val != t) {
			if(t < (*p)->val)
				p = &((*p)->left);
			else if(t > (*p)->val)
				p = &((*p)->right);
		}
		if(*p == sentinel) {
			*p = freenode++;
			(*p)->val = t;
			(*p)->left = (*p)->right = sentinel;
			n++;
		}
	}
	int size(){ return n; }
	void report(int *x)
	{
		v = x;
		vn = 0;
		traverse(root);
	}
private:
	struct node{
		int val;
		node *left, *right;
		node(): val(0), left(0), right(0) { }
	};
	node *root, *sentinel, *freenode;
	int n, *v, vn;

	void traverse(node *p) 
	{
		if(p == sentinel)
			return;
		traverse(p->left);
		v[vn++] = p->val;
		traverse(p->right);
	}

};

int main()
{
	IntSetBST2 bst(100, 1000);
	bst.insert(4); bst.insert(5); bst.insert(1); bst.insert(0); bst.insert(10);
	bst.insert(9); bst.insert(12); bst.insert(7);

	int a[bst.size()];
	bst.report(a);

	cout << bst.size() << endl;
	copy(a, a+bst.size(), ostream_iterator<int>(cout, " "));
	cout << '\n';
}





