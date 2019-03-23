#include <iostream>
#include <stack>
#include <queue>
using namespace std;
#define BinNodePosi(T) BinNode<T>* //节点位置
#define stature(p) ((p) ? (p)->height : -1) //节点高度（与“空树高度为-1”的约定相统一）

//BinNode:
// lChild | parent | rChild
// ------------------------
//            data
// ------------------------
// height |   npl  | color

template<typename T>
struct BinNode
{
	BinNodePosi(T) parent;
	BinNodePosi(T) lChild;
	BinNodePosi(T) rChild;//父亲 孩子
	T data;	//值
	int height;//高度
	int size();//子树规模(后代总数)
	BinNode():parent(NULL), lChild(NULL), rChild(NULL), height(0){}
	BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, \
	BinNodePosi(T) rc = NULL, int h = 0):data(e), parent(p), \
	lChild(lc), rChild(rc), height(h){};
	BinNodePosi(T) insertAsLC(T const &e);//插入为左孩子
	BinNodePosi(T) insertAsRC(T const &e);//插入为右孩子
	// BinNodePosi(T) succ();//中序遍历意义下的直接后继
	// template<typename VST>void travLevel(VST &);//子树层次遍历
	// template<typename VST>void travPre(VST &);//字数先序遍历
	// template<typename VST>void tracIn(VST &);//子树中序遍历
	// template<typename VST>void travPost(VST &);//子树后序遍历
};

template<typename T>
int BinNode<T>::size()
{
	int s = 1;
	if(lChild) s += lChild->size();
	if(rChild) s += rChild->size();
	return s;
}

template<typename T>
BinNodePosi(T) BinNode<T>::insertAsLC(T const &e)
{
	return lChild = new BinNode(e, this);
}

template<typename T>
BinNodePosi(T) BinNode<T>::insertAsRC(T const &e)
{
	return rChild = new BinNode(e, this);
}

template<typename T>
class BinTree
{
protected:
	int _size;//规模
	BinNodePosi(T) _root;//根节点
	virtual int updateHeight(BinNodePosi(T) x);//更新节点x的高度
	void updateHeightAbove(BinNodePosi(T) x);//更新节点x及祖先的高度
public:
	BinTree():_size(0), _root(NULL){} //构造函数
	~BinTree(){if(0<_size) delete _root; } //析构函数
	int size() const {return _size;}//规模
	bool empty() const {return !_root;}//判空
	BinNodePosi(T) root() const{return _root;}//树根	
	BinNodePosi(T) insertAsRoot(T const &e);//作为树根插入空树
	BinNodePosi(T) insertAsLC(BinNodePosi(T), T const &e);//作为左孩子插入
	BinNodePosi(T) insertAsRC(BinNodePosi(T), T const &e);//作为右孩子插入
	void travPre_a(BinNodePosi(T));//先序遍历(递归)
	void travPre_b(BinNodePosi(T));//先序遍历(迭代1)
	void visitAlongLeftBranch(BinNodePosi(T) x, stack<BinNodePosi(T)> &s);//一直遍历左孩子
	void visitAlongLeftBranch_In(BinNodePosi(T) x, stack<BinNodePosi(T)> &s);
	void travPre_c(BinNodePosi(T) x);//先序遍历(迭代2)
	void travIn(BinNodePosi(T) x);//中序遍历
	void travLevel(BinNodePosi(T) x);//层次遍历
};

template<typename T>
int BinTree<T>::updateHeight(BinNodePosi(T) x)
{
	return x->height = 1 + max(stature(x->lChild), stature(x->rChild));
}

template<typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x)
{
	while(x){
		updateHeight(x);
		x = x->parent;
	}
}

template<typename T>BinNodePosi(T)
BinTree<T>::insertAsRoot(T const &e)
{
	_size = 1;
	return _root = new BinNode<T>(e);
}

template<typename T>BinNodePosi(T)
BinTree<T>::insertAsLC(BinNodePosi(T) x, T const &e)
{
	_size++;
	x->insertAsLC(e);
	updateHeightAbove(x);
	return x->lChild;
}

template<typename T>BinNodePosi(T)
BinTree<T>::insertAsRC(BinNodePosi(T) x, T const &e)
{
	_size++;
	x->insertAsRC(e);
	updateHeightAbove(x);
	return x->rChild;
}

template<typename T>
void BinTree<T>::travPre_a(BinNodePosi(T) x)
{
	if(!x)return;
	cout<<x->data<<"\t";
	travPre_a(x->lChild);
	travPre_a(x->rChild);
}

template<typename T>
void BinTree<T>::travPre_b(BinNodePosi(T) x)
{
	stack<BinNodePosi(T)> s;
	if(x) s.push(x);//根节点入栈
	while(!s.empty())
	{
		x = s.top();
		s.pop();
		cout<<x->data<<"\t";
		if(x->rChild)s.push(x->rChild);
		if(x->lChild)s.push(x->lChild);
	}
}

template<typename T>
void BinTree<T>::visitAlongLeftBranch(BinNodePosi(T) x, stack<BinNodePosi(T)> &s)
{
	while(x){
		cout<<x->data<<"\t";
		s.push(x->rChild);//右孩子入栈
		x = x->lChild;//沿左侧链下行
	}
}

template<typename T>
void BinTree<T>::travPre_c(BinNodePosi(T) x)
{
	stack<BinNodePosi(T)> S;
	while(1)
	{
		visitAlongLeftBranch(x, S);
		if(S.empty())break;
		x = S.top();
		S.pop();
	}
}

template<typename T>
void BinTree<T>::visitAlongLeftBranch_In(BinNodePosi(T) x, stack<BinNodePosi(T)> &s)
{
	while(x){
		s.push(x);//入栈
		x = x->lChild;//沿左侧链下行
	}
}

template<typename T>
void BinTree<T>::travIn(BinNodePosi(T) x)
{
	stack<BinNodePosi(T)> S;
	while(1)
	{
		visitAlongLeftBranch_In(x,S);
		if(S.empty())break;
		x=S.top();
		S.pop();
		cout<<x->data<<"\t";
		x = x->rChild;
	}
}

template<typename T>
void BinTree<T>::travLevel(BinNodePosi(T) x)
{
	queue<BinNodePosi(T)> q;
	q.push(x);
	while(!q.empty())
	{
		BinNodePosi(T) x = q.front();
		q.pop();
		cout<<x->data<<"\t";
		if(x->lChild)q.push(x->lChild);
		if(x->rChild)q.push(x->rChild);
	}
}

int main(int argc, char const *argv[])
{
	BinTree<int> BT;
	BT.insertAsRoot(3);
	BinNode<int>* a = BT.insertAsLC(BT.root(), 4);
	BT.insertAsLC(a, 6);
	BT.insertAsRC(a, 7);
	BT.insertAsRC(BT.root(), 5);
	BT.travPre_a(BT.root());
	cout<<endl;
	BT.travPre_b(BT.root());
	cout<<endl;
	BT.travPre_c(BT.root());
	cout<<endl;
	BT.travIn(BT.root());
	cout<<endl;
	BT.travLevel(BT.root());
	cout<<endl;
	return 0;
}