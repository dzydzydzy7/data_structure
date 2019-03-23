#include <iostream>
#include <string>
using namespace std;
#define Posi ListNode*

struct ListNode
{
	int data;
	Posi succ;
	ListNode() { data = -9999; succ = NULL; }
	ListNode(int n, Posi s = NULL) :data(n), succ(s) {}
	Posi insert(int n);
};

Posi ListNode::insert(int n)
{
	Posi x = new ListNode(n, succ);
	succ = x;
	return x;
}

class List
{
private:
	Posi header;
public:
	List();
	List(Posi p);
	~List();
	void insertTrail(int n);
	void insertHead(int n);
	void print();
	void remove(int minn, int maxn);
	void Remove(int r);
	int getMax();
	void fenjie(List &e1, List &e2);
	int differentSet(List &e);
};

List::List()
{
	header = new ListNode;
	header->succ = NULL;
}

List::~List()
{
	header->succ = NULL;
}

List::List(Posi p)
{
	header = new ListNode;
	header->succ = NULL;
	Posi h = header;
	while (p->succ)
	{
		h->succ = p->succ;
		h = h->succ;
		p = p->succ;
	}
}

void List::insertTrail(int n)
{
	Posi h = header;
	while (n--)
	{
		Posi p = new ListNode;
		cin >> p->data;
		p->succ = NULL;
		h->succ = p;
		h = p;
	}
}

void List::insertHead(int n)
{
	Posi h = header;
	Posi p = new ListNode;
	p->data = n;
	p->succ = h->succ;
	h->succ = p;
}

int List::getMax()
{
	int maxn = 1 << 31;
	Posi p = header;
	p = p->succ;
	while (p)
	{
		if (p->data > maxn)maxn = p->data;
		p = p->succ;
	}
	return maxn;
}

void List::fenjie(List &e1, List &e2)
{
	Posi h = header;
	h = h->succ;
	Posi p1 = e1.header;
	Posi p2 = e2.header;
	Posi r;
	while (h)
	{
		r = h->succ;
		if (h->data < 0)
		{
			p1->succ = h;
			p1 = p1->succ;
			p1->succ = NULL;
		}
		else
		{
			p2->succ = h;
			p2 = p2->succ;
			p2->succ = NULL;
		}
		h = r;
	}
}

int List::differentSet(List & e)
{
	int num = 0;
	Posi h = header;
	Posi p = e.header;
	Posi pre = h;
	h = h->succ;
	p = p->succ;
	while (h && p)
	{
		if (h->data < p->data)
		{
			num++;
			pre = h;
			h = h->succ;
		}
		else if (h->data > p->data)
		{
			p = p->succ;
		}
		else
		{
			pre->succ = h->succ;
			Posi eq = h;
			h = h->succ;
			delete eq;
		}
	}
	print();
	return num;
}

void List::print()
{
	int count = 0;
	Posi p = header;
	p = p->succ;
	while (p)
	{
		if (!p->succ) { cout << p->data << endl; }
		else cout << p->data << " ";
		p = p->succ;
		count++;
	}
	//cout << count << endl;
}

void List::remove(int minn, int maxn)
{
	Posi p = header;
	while (p->succ->data < minn && p->succ) p = p->succ;
	Posi r = p->succ;
	while (r->data <= maxn) {
		if (r->succ == NULL) { r = NULL; break; }
		else r = r->succ;
	}
	p->succ = r;
}

void List::Remove(int r)
{
	Posi p = header;
	Posi t = header;
	int i = 0;
	while (p->succ)
	{
		if (i < r) {
			p = p->succ;
			i++;
		}
		else
		{
			p = p->succ;
			t = t->succ;
			i++;
		}
	}
	cout << t->succ->data << endl;
}



int main()
{
	int a;
	while (cin >> a)
	{
		if (a == 0)break;
		List L;
		L.insertTrail(a);
		int c;
		cin >> c;
		L.Remove(c);
	}
	return 0;
}