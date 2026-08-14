#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<fstream>
using namespace std;
struct treenode
{
	char letter;
	struct treenode *leftlink, *rightlink, *uplink;
	treenode();
	treenode(char x, struct treenode *left, struct treenode *right, struct treenode *up);
};
treenode::treenode()
{
	letter = '-';
	leftlink = NULL;
	rightlink = NULL;
}
treenode::treenode(char x, struct treenode *left, struct treenode *right, struct treenode *up)
{
	letter = x;
	leftlink = left;
	rightlink = right;
	uplink = up;
}
class bintree
{
private:
	struct treenode *root;
	int num;
public:
	bintree(char x);
	struct treenode *getroot();
	int height(struct treenode *x);
	int position(struct treenode *x);	// calculate the distance of one node from the root
	int minpos(struct treenode *x);	// calculate the min distance
	void insertleft(char l, struct treenode *x);
	void insertright(char l, struct treenode *x);
	void levelOrderDisp(struct treenode *x);	// traverse in level order
	void preOrderDisp(struct treenode *x);	// traverse in pre order
	void enheap(struct treenode *x);	// make it a min heap
	void filterup(struct treenode *x);	// float up the data of one node
	int getnum(struct treenode *x);	// get the number of nodes in the heap
	struct treenode *traverseb(struct treenode *x, int h);	// get the first leave with the min distance
	void heapinsert(char l);	// insert a node into the heap
	struct treenode *traverseA(struct treenode *x);	// work out the position to insert the node(even number)
	struct treenode *getleave();	// work out the position to insert the node(odd number)
	struct treenode *traverseC(struct treenode *x, int h);	// work out the position of the last node
	void heapsort(struct treenode *x);	// print out the letters in rising order
	void detroy(struct treenode *x);	// destroy the node
};
bintree::bintree(char x)
{
	root = new struct treenode(x, NULL, NULL, NULL);
}
struct treenode *bintree::getroot()
{
	return root;
}
int bintree::height(struct treenode *x)
{
	int lh = 0, rh = 0;
	if (x->leftlink == NULL && x->rightlink == NULL)
		return 1;
	if (x->leftlink != NULL)
		lh = height(x->leftlink);
	if (x->rightlink != NULL)
		rh = height(x->rightlink);
	if (lh >= rh)
		return lh + 1;
	else
		return rh + 1;
}
int bintree::position(struct treenode *x)
{
	int pos;
	if (x->uplink == NULL)
		return 1;
	return position(x->uplink) + 1;
}
int bintree::minpos(struct treenode *x)
{
	int left = 100, right = 100;
	if (x->leftlink == NULL && x->rightlink == NULL)
		return position(x);
	if (x->leftlink != NULL)
		left = minpos(x->leftlink);
	if (x->rightlink != NULL)
		right = minpos(x->rightlink);
	if (left <= right)
		return left;
	else
		return right;
}
struct treenode *bintree::traverseb(struct treenode *x, int h)
{
	struct treenode *p;
	if (x->leftlink == NULL && x->rightlink == NULL && position(x) < h)
		return x;
	else if (x->leftlink == NULL && x->rightlink == NULL)
		return NULL;
	else
	{
		if (x->leftlink != NULL)
		{
			p = traverseb(x->leftlink, h);
			if (p != NULL)
				return p;
		}
		if (x->rightlink != NULL)
		{
			p = traverseb(x->rightlink, h);
			if (p != NULL)
				return p;
		}
		return NULL;
	}
}
void bintree::insertleft(char l, struct treenode *x)
{
	struct treenode *p;
	p = new struct treenode(l, x->leftlink, NULL, x);
	if (x->leftlink != NULL)
		x->leftlink->uplink = p;
	x->leftlink = p;
}
void bintree::insertright(char l, struct treenode *x)
{
	struct treenode *p;
	p = new struct treenode(l, NULL, x->rightlink, x);
	if (x->rightlink != NULL)
		x->rightlink->uplink = p;
	x->rightlink = p;
}
void bintree::levelOrderDisp(struct treenode *x)
{
	struct treenode *nodes[20];
	int s = 0, t = 0;
	nodes[t++] = x;
	while (1)
	{
		if (s == t)
			break;
		if (nodes[s]->leftlink != NULL)
			nodes[t++] = nodes[s]->leftlink;
		if (nodes[s]->rightlink != NULL)
			nodes[t++] = nodes[s]->rightlink;
		cout << nodes[s++]->letter << " ";
	}
}
void bintree::preOrderDisp(struct treenode *x)
{
	if (x != NULL)
	{
		cout << x->letter << " ";
		preOrderDisp(x->leftlink);
		preOrderDisp(x->rightlink);
	}
	return;
}
void bintree::enheap(struct treenode *x)
{
	char left = 'z', right = 'z';
	if (x->leftlink == NULL && x->rightlink == NULL)
		return;
	else if (x->leftlink == NULL && x->rightlink != NULL)
		enheap(x->rightlink);
	else if (x->rightlink == NULL && x->leftlink != NULL)
		enheap(x->leftlink);
	else
	{
		enheap(x->leftlink);
		enheap(x->rightlink);
	}
	if (x->leftlink != NULL)
		left = x->leftlink->letter;
	if (x->rightlink != NULL)
		right = x->rightlink->letter;
	if (right <= left && right < x->letter)
	{
		x->rightlink->letter = x->letter;
		x->letter = right;
		enheap(x->rightlink);
	}
	else if (left <= right && left < x->letter)
	{
		x->leftlink->letter = x->letter;
		x->letter = left;
		enheap(x->leftlink);
	}
}
void bintree::filterup(struct treenode *x)
{
	char temp;
	while (x->uplink != NULL)
	{
		if (x->letter < x->uplink->letter)
		{
			temp = x->letter;
			x->letter = x->uplink->letter;
			x->uplink->letter = temp;
			x = x->uplink;
		}
		else
			break;
	}
}
int bintree::getnum(struct treenode *x)
{
	if (x->leftlink == NULL && x->rightlink == NULL)
		return 1;
	else if (x->leftlink == NULL && x->rightlink != NULL)
		return getnum(x->rightlink) + 1;
	else if (x->rightlink == NULL && x->leftlink != NULL)
		return getnum(x->leftlink) + 1;
	else
		return getnum(x->leftlink) + getnum(x->rightlink) + 1;
}
struct treenode *bintree::traverseA(struct treenode *x)
{
	struct treenode *temp;
	if (x->leftlink != NULL && x->rightlink == NULL)
		return x;
	else
	{
		if (x->leftlink != NULL)
		{
			temp = traverseA(x->leftlink);
			if (temp != NULL)
				return temp;
		}
		if (x->rightlink != NULL)
		{
			temp = traverseA(x->rightlink);
			if (temp != NULL)
				return temp;
		}
		return NULL;
	}
}
struct treenode *bintree::getleave()
{
	struct treenode *p = root;
	int h = height(root);
	if (minpos(root) == h)
	{
		while (p->leftlink != NULL)
			p = p->leftlink;
		return p;
	}
	else
		return traverseb(root, h);
}
void bintree::heapinsert(char l)
{
	struct treenode *x;
	int n = getnum(root);
	if (n % 2 == 0)
	{
		x = traverseA(root);
		x->rightlink = new struct treenode(l, NULL, NULL, x);
		x = x->rightlink;
	}
	else
	{
		x = getleave();
		x->leftlink = new struct treenode(l, NULL, NULL, x);
		x = x->leftlink;
	}
	filterup(x);
}
struct treenode *bintree::traverseC(struct treenode *x, int h)
{
	struct treenode *p;
	if (x->leftlink == NULL && x->rightlink == NULL && position(x) < h)
		return NULL;
	else if (x->leftlink == NULL && x->rightlink == NULL)
		return x;
	else
	{
		if (x->rightlink != NULL)
		{
			p = traverseC(x->rightlink, h);
			if (p != NULL)
				return p;
		}
		if (x->leftlink != NULL)
		{
			p = traverseC(x->leftlink, h);
			if (p != NULL)
				return p;
		}
		return NULL;
	}
}
void bintree::detroy(struct treenode *x)
{
	struct treenode *p = x->uplink;
	if (x->leftlink != NULL)
		detroy(x->leftlink);
	if (x->rightlink != NULL)
		detroy(x->rightlink);
	if (x == p->leftlink)
		p->leftlink = NULL;
	else
		p->rightlink = NULL;
	delete x;
}
void bintree::heapsort(struct treenode *x)
{
	struct treenode *p;
	int n, h;
	while (1)
	{
		cout << root->letter << " ";
		h = height(root);
		p = traverseC(root, h);
		root->letter = p->letter;
		detroy(p);
		enheap(root);
		n = getnum(root);
		cout << n;
		if (n == 1)
		{
			cout << root->letter << endl;
			delete root;
			break;
		}
	}
}
int main()
{
	struct treenode *p;
	bintree bin('G');
	p = bin.getroot();
	bin.insertleft('D', p);
	bin.insertright('B', p);
	p = p->leftlink;
	bin.insertleft('E', p);
	bin.insertright('A', p);
	p = p->leftlink;
	bin.insertleft('S', p);
	bin.insertright('B', p);
	p = p->uplink;
	p = p->rightlink;
	bin.insertleft('C', p);
	bin.insertright('I', p);
	p = bin.getroot();
	p = p->rightlink;
	bin.insertleft('D', p);
	bin.insertright('H', p);
	p = p->leftlink;
	bin.insertleft('M', p);
	bin.insertright('K', p);
	p = p->uplink;
	p = p->rightlink;
	bin.insertleft('W', p);
	bin.insertright('T', p);

	bin.levelOrderDisp(bin.getroot());
	cout << endl;

	bin.enheap(bin.getroot());
	bin.levelOrderDisp(bin.getroot());
	cout << endl;

	bin.heapsort(bin.getroot());
	return 0;
}
