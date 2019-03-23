#include <iostream>
//#include <algorithm>

using namespace std;
class Fib { //Fibonacci数列类 
private:
	int f, g; //f = fib(k - 1), g = fib(k)。均为int型，很快就会数值溢出 
public:
	Fib(int n) //初始化为不小于n的最小Fibonacci项 
	{
		f = 1; g = 0; while (g < n) next();
	} //fib(-1), fib(0)，O(log_phi(n))时间 
	int get() { return g; } //获取当前Fibonacci项，O(1)时间 
	int next() { g += f; f = g - f; return g; } //转至下一Fibonacci项，O(1)时间 
	int prev() { f = g - f; g -= f; return g; } //转至上一Fibonacci项，O(1)时间 
};
template<typename T>
T Max(T a, T b) { return (a > b) ? a : b; }
typedef int Rank;	//秩
#define DEFAULT_CAPACITY 3	//初始容量
template <typename T>
struct Increase {
	virtual void operator()(T& e) { e++; }
};
template <typename T>
class Vector {	//模板类
private:
	Rank _size;		//规模
	int _capacity;	//容量
	T * _elem;		//数据区
public:
	Vector(int c = DEFAULT_CAPACITY); //默认
	Vector(T const *A, Rank low, Rank high);//数组区间复制
	Vector(Vector<T> const &V, Rank low, Rank high); //向量区间复制
	Vector(Vector<T> const &V); //向量整体复制	
	~Vector(); //析构
	void CopyFrom(T const *A, Rank low, Rank high);
	void expand(); //扩容
	void shrink(); //缩容
	void show();
	void test();
	Rank GetSize() { return _size; }
	//徇秩访问,左右值均可访问，因为是引用，可访问左值
	T &operator[](Rank r) const { return _elem[r]; }
	int remove(Rank low, Rank high); //删除low到high的前闭后开区间
	int remove(Rank r); //删除单个元素
	int disorder()const;//相邻逆序对的数目
	int deduplicate();	//无序向量唯一化(繁琐错误)
	int uniquify();		//有序向量唯一化(低效)
	int uniquify_g();	//有序向量唯一化(高效)
	Rank insert(Rank r, T const &e); //插入
	Rank PushBack(T const &e);	//追加
	Rank find(T const &e, Rank low, Rank high);		//在[low， high)查找e
	Rank binsearch_a(T const &e, Rank low, Rank high);//二分查找
	Rank binsearch_b(T const &e, Rank low, Rank high);//减少比较次数返回最大下标
	Rank binsearch_c(T const &e, Rank low, Rank high);//基于b返回不大于e的最下标
	Rank fibsearch_a(T const &e, Rank low, Rank high);//斐波那契查找
	Rank fibsearch_b(T const &e, Rank low, Rank high);//返回不大于e的最下标
	bool bubble(Rank low, Rank high);	//冒泡排序的一次
	void BubbleSort(Rank low, Rank high);//冒泡排序从小到大
	Rank bubble_g(Rank low, Rank high);	//高效的一次冒排
	void BubbleSort_g(Rank low, Rank high);//高效的冒排从小到大O(n)~O(n^2)
	void merage(Rank low, Rank mid, Rank high);//二路归并
	void MerageSort(Rank low, Rank high);//归并排序
};

int main() 
{
	int arr[20] = { 1,1,3,2,0,2,3,2,1,0,1,4,7,0,2,5,8,3,6,9};
	Vector<int> v;
	v.show();
	for (int i = 0; i < 20; i++) {
		v.insert(i, arr[i]);
		v.show();
	}
	v.test();
	v.MerageSort(0, v.GetSize());
	v.test();
	cout << v.binsearch_a(1, 0, v.GetSize()) << endl;
	cout << v.binsearch_b(1, 0, v.GetSize()) << endl;
	cout << v.binsearch_c(1.1, 0, v.GetSize()) << endl;
	cout << v.fibsearch_a(1, 0, v.GetSize()) << endl;
	cout << v.fibsearch_b(1.1, 0, v.GetSize()) << endl;
	v.uniquify_g();
	v.test();
	return 0;
}

template<typename T>
Vector<T>::Vector(int c)
{
	_elem = new T[_capacity = c];
	_size = 0;
}

template<typename T>
Vector<T>::Vector(T const * A, Rank low, Rank high)
{
	CopyFrom(A, low, high);
}

template<typename T>
Vector<T>::Vector(Vector<T> const & V, Rank low, Rank high)
{
	CopyFrom(V._elem, low, high);
}

template<typename T>
Vector<T>::Vector(Vector<T> const & V)
{
	CopyFrom(V._elem, 0, V._size);
}

template<typename T>
Vector<T>::~Vector()
{
	delete[] _elem;
}

template<typename T>
void Vector<T>::CopyFrom(T const * A, Rank low, Rank high)
{
	_elem = new T[_capacity = 2 * (high - low)];
	_size = 0;
	while (low < high)
		_elem[_size++] = A[low++];
}

template<typename T>
void Vector<T>::expand()
{
	if (_size < _capacity) return;
	_capacity = Max(_capacity, DEFAULT_CAPACITY);
	T *oldelem = _elem;//复制_elem的所有元素到oldelem
	_elem = new T[_capacity <<= 1];// <<= 左移等于
	for (int i = 0; i < _size; i++)
		_elem[i] = oldelem[i];
	delete[] oldelem;
}

template<typename T>
void Vector<T>::shrink()
{
	if (_size * 2 > _capacity) return;
	_capacity = Max(_size * 2, DEFAULT_CAPACITY);
	T *oldelem = _elem;//复制_elem的所有元素到oldelem
	_elem = new T[_capacity];
	for (int i = 0; i < _size; i++)
		_elem[i] = oldelem[i];
	delete[] oldelem;
}

template<typename T>
Rank Vector<T>::insert(Rank r, T const & e)
{
	if (_size + 1 > _capacity)expand();//必要时扩容
	for (int i = _size; i > r; i--)
		_elem[i] = _elem[i - 1]; //依次后移
	_elem[r] = e;	//在r位置插入e
	_size++;	//更新size
	return r;	//返回秩
}

template<typename T>
Rank Vector<T>::PushBack(T const & e)
{
	if (_size + 1 > _capacity)expand();//必要时扩容
	_elem[_size++] = e;
	return _size;
}

template<typename T>
int Vector<T>::remove(Rank low, Rank high)
{
	if (low == high)return 0;
	while (high < _size)_elem[low++] = _elem[high++];
	_size = low; //
	if ((_size * 2) < _capacity)shrink();//如果size过小，缩容
	return high - low;	//返回删除元素数
}

template<typename T>
int Vector<T>::remove(Rank r)
{
	T e = _elem[r];
	remove(r, r + 1);
	return e;	//返回删除元素的值
}

template<typename T>
int Vector<T>::disorder() const
{
	int n = 0;
	for (int i = 1; i < _size; i++)
		n += (_elem[i] < _elem[i - 1]);
	return n;
}

template<typename T>
int Vector<T>::deduplicate()
{
	int oldsize = _size;
	Rank i = 1;
	while (i < _size)
		(find(_elem[i], 0, i) < 0) ? i++ : remove(i);
	return oldsize - _size;
}

template<typename T>
int Vector<T>::uniquify()
{
	int oldsize = _size;
	int i = 0;
	while (i < _size - 1)
		(_elem[i] == _elem[i + 1]) ? remove(i + 1) : i++;//每次调用remove，O(n^2)
	return oldsize - _size;
}

template<typename T>
int Vector<T>::uniquify_g()
{
	Rank i = 0, j = 0;
	while (++j < _size)		
		if (_elem[i] != _elem[j]) _elem[++i] = _elem[j];//不同的元素移到不重复的右侧
	_size = ++i;		//等效于size = i + 1，而size=i++则为size = i
	shrink();	
	return j - i;	//避开了remove，高效
}

template<typename T>
Rank Vector<T>::find(T const & e, Rank low, Rank high)
{
	while ((low < high--) && (_elem[high] != e));//_elem[high]中的high已经减过
	//high = low时也要判断，若未找到，high = low - 1
	//if (high < low)return -1;
	return high;	//返回下标，high<low即未找到
}

template<typename T>
Rank Vector<T>::binsearch_a(T const & e, Rank low, Rank high)
{	//左中右三种情况
	while (low < high) {
		Rank mid = (low + high) >> 1;//右移向下取整
		if (e < _elem[mid])high = mid;
		else if (_elem[mid] < e)low = mid + 1;
		else return mid;
	}
	return -1;	//查找失败时返回-1
}

template<typename T>
Rank Vector<T>::binsearch_b(T const & e, Rank low, Rank high)
{	//只有左右两种情况
	while (1 < high - low) {
		Rank mid = (high + low) >> 1;
		(e < _elem[mid]) ? high = mid : low = mid;
	}
	return (e == _elem[low]) ? low : -1;
}

template<typename T>
Rank Vector<T>::binsearch_c(T const & e, Rank low, Rank high)
{
	while (low < high) {
		Rank mid = (low + high) >> 1;
		(e < _elem[mid]) ? high = mid : low = mid + 1;
	}
	return --low;//返回不大于e的最下标 
}

template<typename T>
Rank Vector<T>::fibsearch_a(T const & e, Rank low, Rank high)
{
	Fib fib(high - low);
	while (low < high) {
		while (high - low < fib.get())fib.prev();//找适合大小的斐波那契数
		Rank mid = low + fib.get() - 1;//按黄金比例切分
		if (e < _elem[mid])high = mid;
		else if (_elem[mid] < e)low = mid + 1;
		else return mid;
	}
	return -1;
}

template<typename T>
Rank Vector<T>::fibsearch_b(T const & e, Rank low, Rank high)
{
	Fib fib(high - low);
	while (low < high){
		while (high - low < fib.get())fib.prev();
		Rank mid = low + fib.get() - 1;
		(e < _elem[mid]) ? high = mid : low = mid + 1;
	}
	return --low;
}
template<typename T>
bool Vector<T>::bubble(Rank low, Rank high)
{
	bool sorted = true;//是否有序
	while (++low < high) {
		if (_elem[low - 1] > _elem[low]) {
			sorted = false;
			swap(_elem[low - 1], _elem[low]); //swap在iostream中
		}
	}
	return sorted;
}

template<typename T>
void Vector<T>::BubbleSort(Rank low, Rank high)
{
	while (!bubble(low, high--));//逐趟交换直至全序
}

template<typename T>
Rank Vector<T>::bubble_g(Rank low, Rank high)
{
	Rank last = low;
	while (++low < high) {
		if (_elem[low - 1] > _elem[low]) {
			last = low;
			swap(_elem[low - 1], _elem[low]);
		}
	}
	return last;
}

template<typename T>
void Vector<T>::BubbleSort_g(Rank low, Rank high)
{
	while (low < (high = bubble_g(low, high)));
	//while (low < high)high = bubble_g(low, high);
}

template<typename T>
void Vector<T>::merage(Rank low, Rank mid, Rank high)
{
	T *A = _elem + low;	//相当于A[i++]=_elem[low++],这种复制方法改变A时_elem也随之改变
	int lb = mid - low;
	T *B = new T[lb];	//B是左半数组
	for (Rank i = 0; i < lb; i++)B[i] = A[i];
	int rc = high - mid;
	T *C = _elem + mid;	//C是右半数组
	for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < rc);) {
		if ((j < lb) && ((rc <= k) || (B[j] <= C[k])))A[i++] = B[j++];
		//B有且(C没 或 B第一个元素<=比C第一个元素)
		if ((k < rc) && ((lb <= j) || (C[k] < B[j])))A[i++] = C[k++];
		//C有且(B没 或 B第一个元素>比C第一个元素)
	}
	delete[] B;
}

template<typename T>
void Vector<T>::MerageSort(Rank low, Rank high)
{
	if (high - low < 2)return;
	int mid = (low + high) >> 1;
	MerageSort(low, mid);
	MerageSort(mid, high);
	merage(low, mid, high);
}

template<typename T>
void Vector<T>::show()
{
	cout << "size: " << _size << ", capacity: " << _capacity;
	cout << ", disorder: " << disorder() << endl;
}

template<typename T>
void Vector<T>::test()
{
	show();
	for (int i = 0; i < GetSize(); i++) cout << _elem[i] << " ";
	cout << endl;
}