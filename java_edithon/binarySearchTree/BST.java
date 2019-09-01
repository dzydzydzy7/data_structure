package binarySearchTree;

import binTree.*;

public class BST<T extends Comparable<? super T>> extends BinTree<T> {
	protected BinNode<T> _hot; // 命中节点的父节点

	public BST() {
		super();
		_hot = null;
	}

	// 从节点v开始查找， e为要查找的值
	private BinNode<T> searchIn(BinNode<T> v, T e) {
		if (v == null || e == v.data)
			return v; // 确定查找成功或失败
		_hot = v; // 记下当前非空节点
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
		BinNode<T> del = x; // 实际被删除的节点
		BinNode<T> succ = null; // 被删除节点的代替者

		if (x.lChild == null && x.rChild == null) {
			_hot = del.parent;
			if (_hot.isGreaterThan(x))
				_hot.lChild = null;
			else
				_hot.rChild = null;
		}

		// 只有左子树或只有右子树可以直接用子树代替该节点
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
		} else { // 左右子树都有时
			del = del.succ();
			// 要删除节点的和它的直接后继交换
			T temp = x.data;
			x.data = del.data;
			del.data = temp;

			BinNode<T> u = del.parent;
			_hot = del.parent;
			if (u.isEqual(x)) { // 交换相邻两层
				u.rChild = (succ = del.rChild);
				if (succ != null) {
					succ.parent = _hot;
					_hot.rChild = succ;
				}
			} else { // 交换不相邻的两层
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
			return false; // 找不到被删除节点，返回false
		// removeAt(x);

		// 删除节点部分
		BinNode<T> del = x; // 实际被删除的节点
		BinNode<T> delPar = x.parent; // 被删除节点的父节点
		BinNode<T> succ = null; // 被删除节点的代替者

		// 只有左子树或只有右子树可以直接用子树代替该节点
		if (x.lChild == null)
			succ = (delPar.rChild = x.rChild);
		else if (x.rChild == null)
			succ = (delPar.rChild = x.lChild);
		else { // 左右子树都有时
			del = del.succ();
			// 要删除节点的和它的直接后继交换
			T temp = x.data;
			x.data = del.data;
			del.data = temp;

			BinNode<T> u = del.parent;
			if (u.isEqual(x)) { // 交换相邻两层
				u.rChild = (succ = del.rChild);
			} else { // 交换不相邻的两层
				u.lChild = (succ = del.rChild);
			}
		}

		_hot = del.parent; // _hot记录当前节点的父节点
		if (succ != null)
			succ.parent = _hot;

		_size--; // 节点数减一
		updateHeightAbove(_hot); // 更新树高
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
	
	protected BinNode<T> rotateAt(BinNode<T> v){	// 参数是孙子节点
		BinNode<T> p = v.parent;
		BinNode<T> g = p.parent;
		if(g.lChild == p) {	// zig
			if(p.lChild == v) {	// zig-zig
				p.parent = g.parent; // 向上连接
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

	public boolean isBlanceed(BinNode<T> x) { // 理想平衡
		return getHeight(x.lChild) == getHeight(x.rChild);
	}

	public int balFac(BinNode<T> x) { // 平衡因子
		return getHeight(x.lChild) - getHeight(x.rChild);
	}

	public boolean avlBalenced(BinNode<T> x) { // avl平衡条件
		return (balFac(x) > -2) && (balFac(x) < 2);
	}
}
