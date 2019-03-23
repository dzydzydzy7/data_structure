#include <iostream>
//#include <algorithm>

using namespace std;
class Fib { //Fibonacci������ 
private:
	int f, g; //f = fib(k - 1), g = fib(k)����Ϊint�ͣ��ܿ�ͻ���ֵ��� 
public:
	Fib(int n) //��ʼ��Ϊ��С��n����СFibonacci�� 
	{
		f = 1; g = 0; while (g < n) next();
	} //fib(-1), fib(0)��O(log_phi(n))ʱ�� 
	int get() { return g; } //��ȡ��ǰFibonacci�O(1)ʱ�� 
	int next() { g += f; f = g - f; return g; } //ת����һFibonacci�O(1)ʱ�� 
	int prev() { f = g - f; g -= f; return g; } //ת����һFibonacci�O(1)ʱ�� 
};
template<typename T>
T Max(T a, T b) { return (a > b) ? a : b; }
typedef int Rank;	//��
#define DEFAULT_CAPACITY 3	//��ʼ����
template <typename T>
struct Increase {
	virtual void operator()(T& e) { e++; }
};
template <typename T>
class Vector {	//ģ����
private:
	Rank _size;		//��ģ
	int _capacity;	//����
	T * _elem;		//������
public:
	Vector(int c = DEFAULT_CAPACITY); //Ĭ��
	Vector(T const *A, Rank low, Rank high);//�������临��
	Vector(Vector<T> const &V, Rank low, Rank high); //�������临��
	Vector(Vector<T> const &V); //�������帴��	
	~Vector(); //����
	void CopyFrom(T const *A, Rank low, Rank high);
	void expand(); //����
	void shrink(); //����
	void show();
	void test();
	Rank GetSize() { return _size; }
	//���ȷ���,����ֵ���ɷ��ʣ���Ϊ�����ã��ɷ�����ֵ
	T &operator[](Rank r) const { return _elem[r]; }
	int remove(Rank low, Rank high); //ɾ��low��high��ǰ�պ�����
	int remove(Rank r); //ɾ������Ԫ��
	int disorder()const;//��������Ե���Ŀ
	int deduplicate();	//��������Ψһ��(��������)
	int uniquify();		//��������Ψһ��(��Ч)
	int uniquify_g();	//��������Ψһ��(��Ч)
	Rank insert(Rank r, T const &e); //����
	Rank PushBack(T const &e);	//׷��
	Rank find(T const &e, Rank low, Rank high);		//��[low�� high)����e
	Rank binsearch_a(T const &e, Rank low, Rank high);//���ֲ���
	Rank binsearch_b(T const &e, Rank low, Rank high);//���ٱȽϴ�����������±�
	Rank binsearch_c(T const &e, Rank low, Rank high);//����b���ز�����e�����±�
	Rank fibsearch_a(T const &e, Rank low, Rank high);//쳲���������
	Rank fibsearch_b(T const &e, Rank low, Rank high);//���ز�����e�����±�
	bool bubble(Rank low, Rank high);	//ð�������һ��
	void BubbleSort(Rank low, Rank high);//ð�������С����
	Rank bubble_g(Rank low, Rank high);	//��Ч��һ��ð��
	void BubbleSort_g(Rank low, Rank high);//��Ч��ð�Ŵ�С����O(n)~O(n^2)
	void merage(Rank low, Rank mid, Rank high);//��·�鲢
	void MerageSort(Rank low, Rank high);//�鲢����
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
	T *oldelem = _elem;//����_elem������Ԫ�ص�oldelem
	_elem = new T[_capacity <<= 1];// <<= ���Ƶ���
	for (int i = 0; i < _size; i++)
		_elem[i] = oldelem[i];
	delete[] oldelem;
}

template<typename T>
void Vector<T>::shrink()
{
	if (_size * 2 > _capacity) return;
	_capacity = Max(_size * 2, DEFAULT_CAPACITY);
	T *oldelem = _elem;//����_elem������Ԫ�ص�oldelem
	_elem = new T[_capacity];
	for (int i = 0; i < _size; i++)
		_elem[i] = oldelem[i];
	delete[] oldelem;
}

template<typename T>
Rank Vector<T>::insert(Rank r, T const & e)
{
	if (_size + 1 > _capacity)expand();//��Ҫʱ����
	for (int i = _size; i > r; i--)
		_elem[i] = _elem[i - 1]; //���κ���
	_elem[r] = e;	//��rλ�ò���e
	_size++;	//����size
	return r;	//������
}

template<typename T>
Rank Vector<T>::PushBack(T const & e)
{
	if (_size + 1 > _capacity)expand();//��Ҫʱ����
	_elem[_size++] = e;
	return _size;
}

template<typename T>
int Vector<T>::remove(Rank low, Rank high)
{
	if (low == high)return 0;
	while (high < _size)_elem[low++] = _elem[high++];
	_size = low; //
	if ((_size * 2) < _capacity)shrink();//���size��С������
	return high - low;	//����ɾ��Ԫ����
}

template<typename T>
int Vector<T>::remove(Rank r)
{
	T e = _elem[r];
	remove(r, r + 1);
	return e;	//����ɾ��Ԫ�ص�ֵ
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
		(_elem[i] == _elem[i + 1]) ? remove(i + 1) : i++;//ÿ�ε���remove��O(n^2)
	return oldsize - _size;
}

template<typename T>
int Vector<T>::uniquify_g()
{
	Rank i = 0, j = 0;
	while (++j < _size)		
		if (_elem[i] != _elem[j]) _elem[++i] = _elem[j];//��ͬ��Ԫ���Ƶ����ظ����Ҳ�
	_size = ++i;		//��Ч��size = i + 1����size=i++��Ϊsize = i
	shrink();	
	return j - i;	//�ܿ���remove����Ч
}

template<typename T>
Rank Vector<T>::find(T const & e, Rank low, Rank high)
{
	while ((low < high--) && (_elem[high] != e));//_elem[high]�е�high�Ѿ�����
	//high = lowʱҲҪ�жϣ���δ�ҵ���high = low - 1
	//if (high < low)return -1;
	return high;	//�����±꣬high<low��δ�ҵ�
}

template<typename T>
Rank Vector<T>::binsearch_a(T const & e, Rank low, Rank high)
{	//�������������
	while (low < high) {
		Rank mid = (low + high) >> 1;//��������ȡ��
		if (e < _elem[mid])high = mid;
		else if (_elem[mid] < e)low = mid + 1;
		else return mid;
	}
	return -1;	//����ʧ��ʱ����-1
}

template<typename T>
Rank Vector<T>::binsearch_b(T const & e, Rank low, Rank high)
{	//ֻ�������������
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
	return --low;//���ز�����e�����±� 
}

template<typename T>
Rank Vector<T>::fibsearch_a(T const & e, Rank low, Rank high)
{
	Fib fib(high - low);
	while (low < high) {
		while (high - low < fib.get())fib.prev();//���ʺϴ�С��쳲�������
		Rank mid = low + fib.get() - 1;//���ƽ�����з�
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
	bool sorted = true;//�Ƿ�����
	while (++low < high) {
		if (_elem[low - 1] > _elem[low]) {
			sorted = false;
			swap(_elem[low - 1], _elem[low]); //swap��iostream��
		}
	}
	return sorted;
}

template<typename T>
void Vector<T>::BubbleSort(Rank low, Rank high)
{
	while (!bubble(low, high--));//���˽���ֱ��ȫ��
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
	T *A = _elem + low;	//�൱��A[i++]=_elem[low++],���ָ��Ʒ����ı�Aʱ_elemҲ��֮�ı�
	int lb = mid - low;
	T *B = new T[lb];	//B���������
	for (Rank i = 0; i < lb; i++)B[i] = A[i];
	int rc = high - mid;
	T *C = _elem + mid;	//C���Ұ�����
	for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < rc);) {
		if ((j < lb) && ((rc <= k) || (B[j] <= C[k])))A[i++] = B[j++];
		//B����(Cû �� B��һ��Ԫ��<=��C��һ��Ԫ��)
		if ((k < rc) && ((lb <= j) || (C[k] < B[j])))A[i++] = C[k++];
		//C����(Bû �� B��һ��Ԫ��>��C��һ��Ԫ��)
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