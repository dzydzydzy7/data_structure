package binarySearchTree;

import binTree.BinNode;

public class AVL<T extends Comparable<? super T>> extends BST<T> {
	public BinNode<T> insert(T e) {
		BinNode<T> x = search(e);
		if(x != null) return x;	//	已有则不能插入
		//x = insertAsLC(_hot, e);	// 创建新节点
		if (_hot.isGreaterThan(e)) {
			insertAsLC(_hot, e);
			x = _hot.lChild;
		} else {
			insertAsRC(_hot, e);
			x = _hot.rChild;
		}
		_size++;
		BinNode<T> xx = x;
		
		// 从x的父亲出发依次向上，一次检查各代祖先g
		for(BinNode<T> g = x.parent; g != null; g = g.parent) {
			if(!avlBalenced(g)) {	// 发现失衡，进行调整
				//FromParentTo(g) = rotateAt(tallerChild(tallerChild(g)));
				BinNode<T> gp = g.parent;
				BinNode<T> head = rotateAt(tallerChild(tallerChild(g)));
				if(gp != null) {
					if(gp.isGreaterThan(g))gp.lChild = head;
					else gp.rChild = head;		
					head.parent = gp;
					updateHeight(gp);
				}
				else this._root = head;
				break;
			}
			else	// 没有失衡，更新高度
				updateHeight(g);
		}
		return xx;
	}
	
	private BinNode<T> tallerChild(BinNode<T> g) {
		if(g.lChild != null && g.rChild == null) return g.lChild;
		if(g.lChild == null && g.rChild != null) return g.rChild;
		if(g.lChild.height > g.rChild.height) return g.lChild;
		return g.rChild;
	}

	public boolean remove(T e) {
		BinNode<T> x = search(e);
		if(x == null) return false;
		removeAt(x);
		_size--;
		
		for(BinNode<T> g = _hot; g != null; g = g.parent) {
			if(!avlBalenced(g)) {
				// g = FromParentTo(g) = rotateAt(tallerChild(tallerChild(g)))
				BinNode<T> gp = g.parent;
				BinNode<T> head = rotateAt(tallerChild(tallerChild(g)));
				if(gp.isGreaterThan(g))gp.lChild = head;
				else gp.rChild = head;
				head.parent = gp;
				g = head;
				
			}
			updateHeight(g);
		}
		return true;		
	}
}
