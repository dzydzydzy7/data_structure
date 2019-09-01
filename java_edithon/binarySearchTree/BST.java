package binarySearchTree;

import binTree.*;

public class BST<T extends Comparable<? super T>> extends BinTree<T> {
	protected BinNode<T> _hot; // ���нڵ�ĸ��ڵ�

	public BST() {
		super();
		_hot = null;
	}

	// �ӽڵ�v��ʼ���ң� eΪҪ���ҵ�ֵ
	private BinNode<T> searchIn(BinNode<T> v, T e) {
		if (v == null || e == v.data)
			return v; // ȷ�����ҳɹ���ʧ��
		_hot = v; // ���µ�ǰ�ǿսڵ�
		if (v.isGreaterThan(e))
			return searchIn(v.lChild, e);
		else
			return searchIn(v.rChild, e);
	}

	public BinNode<T> search(T e) {
		return searchIn(_root, e);
	}

	public BinNode<T> insert(T e) {
		BinNode<T> x = search(e);
		if (x == null) {
			if (_hot.isGreaterThan(e)) {
				insertAsLC(_hot, e);
				x = _hot.lChild;
			} else {
				insertAsRC(_hot, e);
				x = _hot.rChild;
			}
			_size++;
			updateHeightAbove(x);
		}
		return x;
	}

	protected BinNode<T> removeAt(BinNode<T> x) {
		BinNode<T> del = x; // ʵ�ʱ�ɾ���Ľڵ�
		BinNode<T> succ = null; // ��ɾ���ڵ�Ĵ�����

		if (x.lChild == null && x.rChild == null) {
			_hot = del.parent;
			if (_hot.isGreaterThan(x))
				_hot.lChild = null;
			else
				_hot.rChild = null;
		}

		// ֻ����������ֻ������������ֱ������������ýڵ�
		else if (x.lChild == null) {
			succ = (x = x.rChild);
			_hot = del.parent;
			if (succ != null) {
				succ.parent = _hot;
				if (_hot.isGreaterThan(succ))
					_hot.lChild = succ;
				else
					_hot.rChild = succ;
			}
		} else if (x.rChild == null) {
			succ = (x = x.lChild);
			_hot = del.parent;
			if (succ != null) {
				succ.parent = _hot;
				if (_hot.isGreaterThan(succ))
					_hot.lChild = succ;
				else
					_hot.rChild = succ;
			}
		} else { // ������������ʱ
			del = del.succ();
			// Ҫɾ���ڵ�ĺ�����ֱ�Ӻ�̽���
			T temp = x.data;
			x.data = del.data;
			del.data = temp;

			BinNode<T> u = del.parent;
			_hot = del.parent;
			if (u.isEqual(x)) { // ������������
				u.rChild = (succ = del.rChild);
				if (succ != null) {
					succ.parent = _hot;
					_hot.rChild = succ;
				}
			} else { // ���������ڵ�����
				u.lChild = (succ = del.rChild);
				if (succ != null) {
					succ.parent = _hot;
					_hot.lChild = succ;
				}
			}
		}
		return succ;
	}

	public boolean remove(T e) {
		BinNode<T> x = search(e);
		if (x == null)
			return false; // �Ҳ�����ɾ���ڵ㣬����false
		// removeAt(x);

		// ɾ���ڵ㲿��
		BinNode<T> del = x; // ʵ�ʱ�ɾ���Ľڵ�
		BinNode<T> delPar = x.parent; // ��ɾ���ڵ�ĸ��ڵ�
		BinNode<T> succ = null; // ��ɾ���ڵ�Ĵ�����

		// ֻ����������ֻ������������ֱ������������ýڵ�
		if (x.lChild == null)
			succ = (delPar.rChild = x.rChild);
		else if (x.rChild == null)
			succ = (delPar.rChild = x.lChild);
		else { // ������������ʱ
			del = del.succ();
			// Ҫɾ���ڵ�ĺ�����ֱ�Ӻ�̽���
			T temp = x.data;
			x.data = del.data;
			del.data = temp;

			BinNode<T> u = del.parent;
			if (u.isEqual(x)) { // ������������
				u.rChild = (succ = del.rChild);
			} else { // ���������ڵ�����
				u.lChild = (succ = del.rChild);
			}
		}

		_hot = del.parent; // _hot��¼��ǰ�ڵ�ĸ��ڵ�
		if (succ != null)
			succ.parent = _hot;

		_size--; // �ڵ�����һ
		updateHeightAbove(_hot); // ��������
		return true;
	}

	protected BinNode<T> connect34(BinNode<T> a, BinNode<T> b, BinNode<T> c, BinNode<T> t0, BinNode<T> t1,
			BinNode<T> t2, BinNode<T> t3) {
		a.lChild = t0;
		if(t0 != null)t0.parent = a;
		a.rChild = t1;
		if(t1 != null)t1.parent = a;
		updateHeight(a);
		c.lChild = t2;
		if(t2 != null)t2.parent = c;
		c.rChild = t3;
		if(t3 != null)t3.parent = c;
		updateHeight(c);
		b.lChild = a;
		a.parent = b;
		b.rChild = c;
		c.parent = b;
		updateHeight(b);
		return b;
	}
	
	protected BinNode<T> rotateAt(BinNode<T> v){	// ���������ӽڵ�
		BinNode<T> p = v.parent;
		BinNode<T> g = p.parent;
		if(g.lChild == p) {	// zig
			if(p.lChild == v) {	// zig-zig
				p.parent = g.parent; // ��������
				return connect34(v, p, g, v.lChild, v.rChild, p.rChild, g.rChild);
			}
			else {	// zig-zag
				v.parent = g.parent;
				return connect34(p, v, g, p.lChild, v.lChild, v.rChild, g.rChild);
			}
		}
		else {	// zag
			if(p.lChild == v) {	// zag-zig
				v.parent = g.parent;
				return connect34(g, v, p, g.lChild, v.lChild, v.rChild, p.rChild);
			}
			else {	// zag-zag
				p.parent = g.parent;
				return connect34(g, p, v, g.lChild, p.lChild, v.lChild, v.rChild);
			}
		}
			
	}

	private int getHeight(BinNode<T> x) {
		if (x == null)
			return -1;
		return x.height;
	}

	public boolean isBlanceed(BinNode<T> x) { // ����ƽ��
		return getHeight(x.lChild) == getHeight(x.rChild);
	}

	public int balFac(BinNode<T> x) { // ƽ������
		return getHeight(x.lChild) - getHeight(x.rChild);
	}

	public boolean avlBalenced(BinNode<T> x) { // avlƽ������
		return (balFac(x) > -2) && (balFac(x) < 2);
	}
}
