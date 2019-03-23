#include <iostream>
using namespace std;
typedef int Rank;
#define Posi(T) ListNode<T>*	//列表节点位置
//节点叫法：头 首 末 尾
template<typename T>
struct ListNode
{
	T data;	//数值
	Posi(T) pred;	//前驱
	Posi(T) succ;	//后继
	ListNode() {}	//针对header和trailer的构造
	ListNode(T e, Posi(T) p = NULL, Posi(T) s = NULL) : data(e), pred(p), succ(s) {}//默认构造器
	Posi(T) insertAsPred(T const &e);//前插入
	Posi(T) insertAsSucc(T const &e);//后插入
};

template<typename T>
Posi(T) ListNode<T>::insertAsPred(T const &e)
{
	Posi(T) x = new ListNode(e, pred, this);//新节点的前驱后继
	pred->succ = x;//旧前去的后继为新节点
	pred = x;//this的前驱为新节点
	return x;//四个指向完成返回x
}

template<typename T>
Posi(T) ListNode<T>::insertAsSucc(T const &e)
{
	Posi(T) x = new ListNode(e, this, succ);
	succ->pred = x;
	succ = x;
	return x;
}

template<typename T>
class List
{
private:
	int _size; //容量
	Posi(T) header;	//头节点
	Posi(T) trailer;//尾节点
protected:
	void init();//列表创建时的初始化
	void copyNodes(Posi(T) p, int n);//复制构造
	int clear();//清空列表
public:
	List() { init(); }
	~List();
	void show();
	int deduplicate();//无序唯一化
	int uniquify();//有序唯一化
	T &operator[](Rank r) const;//徇秩访问，效率低
	T remove(Posi(T) p);//删除节点
	Posi(T) first() const { return header->succ; }//首节点位置
	Posi(T) last() const { return trailer->pred; }//末节点位置
	//以p为根节点，在他的n个真前驱中找e
	Posi(T) find(T const &e, int n, Posi(T) p) const;
	//p的n个真前驱中，找到不大于e的最后者
	Posi(T) search(T const &e, int n, Posi(T) p) const;
	Posi(T) insertAsFrist(T const &e);//将e作为首节点插入
	Posi(T) insertAsLast(T const &e);//将e作为末节点插入
	Posi(T) insertBefore(Posi(T) p, T const &e);//e作为p的前驱插入
	Posi(T) insertAfter(Posi(T) p, T const &e);//e作为p的后继插入	
	void selectionSort(Posi(T) p, int n);//p后的n个节点选择排序
	Posi(T) selectMax(Posi(T) p, int n);//选出最大值
	void insertionSort(Posi(T) p, int n);//p后的n个节点插入排序
};

template<typename T>
void List<T>::init()
{
	header = new ListNode<T>;//创建头哨兵
	trailer = new ListNode<T>;//创建尾哨兵
	header->succ = trailer;
	header->pred = NULL;
	trailer->pred = header;
	trailer->succ = NULL;
	_size = 0;
}

template<typename T>
void List<T>::copyNodes(Posi(T) p, int n)
{
	init();//创建头尾
	while(n--)//起自p的n项依次作为末节点插入
	{
		insertAsPred(p->data);
		p = p->succ;
	}
}

template<typename T>
int List<T>::clear()
{
	int oldsize = _size;
	while(0 < _size) remove(header->succ);
	return oldsize;
}

template<typename T>
List<T>::~List()
{
	clear();
	delete header;
	delete trailer;
}

template<typename T>
int List<T>::deduplicate()
{
	if(_size < 2) return 0;
	int oldsize = _size;
	Posi(T) p = first();//从首节点起
	Rank r = 1;
	while(trailer != (p = p->succ))
	{//依次查找每一个元素是否在前驱中存在
		Posi(T) q = find(p->data, r, p);
		q?remove(q):r++;//存在就删除
	}
	return oldsize - _size;
}

template<typename T>
int List<T>::uniquify()
{
	if(_size < 2) return 0;
	int oldsize = _size;
	Posi(T) p = first();
	Posi(T) q;
	while(trailer != (q = p->succ))
		if(p->data != q->data)p = q;
		else remove(q);
	return oldsize - _size;
}

template<typename T>
T &List<T>::operator[](Rank r) const //&是后加上去的
{
	Posi(T) p = first(); 	//从首节点出发
	while(0 < r--) p = p->succ; //数出第r个节点
	return p->data;
}

template<typename T>
T List<T>::remove(Posi(T) p)
{
	T e = p->data;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p;
	_size--;
	return e;
}

template<typename T>
Posi(T) List<T>::find(T const &e, int n, Posi(T) p) const
{
	while(0 < n--)
		if(e == (p = p->pred)->data) return p;
	return NULL;
}

template<typename T>
Posi(T) List<T>::search(T const &e, int n, Posi(T) p) const
{
	while(0 <= n--)
		if(((p = p->pred)->data) <= e) break;
	return p;	
}

template<typename T>
Posi(T) List<T>::insertAsFrist(T const &e)
{
	_size++;
	return header->insertAsSucc(e);
}

template<typename T>
Posi(T) List<T>::insertAsLast(T const &e)
{
	_size++;
	return trailer->insertAsPred(e);
}

template<typename T>
Posi(T) List<T>::insertBefore(Posi(T) p, T const &e)
{
	_size++;
	return p->insertAsPred(e);
}

template<typename T>
Posi(T) List<T>::insertAfter(Posi(T) p, T const &e)
{
	_size++;
	return p->insertAsSucc(e);
}

template<typename T>
void List<T>::selectionSort(Posi(T) p, int n)
{
	Posi(T) head = p->pred;
	Posi(T) tail = p;
	for(int i = 0; i < n; i++) tail = tail->succ;
	while(1 < n)
	{
		insertBefore(tail, remove(selectMax(head->succ, n)));
		tail = tail->pred;//每次把最大的放到tail前面，tail前移
		n--;
	}
}

template<typename T>
Posi(T) List<T>::selectMax(Posi(T) p, int n)
{
	Posi(T) max = p;
	for(Posi(T) cur = p; 1 < n; n--)
		if(((cur = cur->succ)->data) >= (max->data))//若cur>=max
			max = cur;
	return max;//返回最大节点位置 
}

template<typename T>
void List<T>::insertionSort(Posi(T) p, int n)
{
	for (int i = 0; i < n; ++i)
	{//假想前面有一个区域i，把p插入到i的合适位置，这样有序的部分一直增大
		insertAfter(search(p->data, i, p), p->data);
		p = p->succ;
		remove(p->pred);
	}
}//一次插入对应一次销毁，O(1)辅助空间，原地操

template<typename T>
void List<T>::show()
{
	cout<<_size<<"\t";
	Posi(T) p = first();
	for (int i = 0; i < _size; ++i)
	{
		cout<<p->data<<" ";
		p = p->succ;
	}
	cout<<endl;
}

template<typename T>
class Queue:public List<T>
{
public:
	void enqueue(T const &e) {this->insertAsLast(e);}
	T dequeue() {return this->remove(this->first());}
	T &front() {return this->first()->data;}
};

int main(int argc, char const *argv[])
{
	Queue<int> q;
	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);
	cout<<q.front()<<endl;
	cout<<q.dequeue()<<endl;
	cout<<q.front()<<endl;
	cout<<q.dequeue()<<endl;
	cout<<q.front()<<endl;
	cout<<q.dequeue()<<endl;
	return 0;
}