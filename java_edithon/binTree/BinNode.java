package binTree;

public class BinNode<T> {
	public BinNode<T> parent;
	public BinNode<T> lChild;
	public BinNode<T> rChild;
	
	public T data;
	public int height;	// 节点高度
	
	public BinNode(BinNode<T> parent, BinNode<T> lChild, BinNode<T> rChild) {
		this.parent = parent;
		this.lChild = lChild;
		this.rChild = rChild;
		height = 0;
	}
	
	public BinNode(BinNode<T> parent, BinNode<T> lChild, BinNode<T> rChild, T data, int height){
		this.parent = parent;
		this.lChild = lChild;
		this.rChild = rChild;
		this.data = data;
		this.height = height;
	}
	
	// 子树的节点数
	public int size() {
		int s = 1;
		if(lChild != null) s += lChild.size();
		if(rChild != null) s += rChild.size();
		return s;
	}
	
	// 作为左孩子插入
	public BinNode<T> insertAsLc(T e){
		return lChild = new BinNode<T>(this, (BinNode<T>)null, (BinNode<T>)null, e, 0);
	}
	
	// 作为右孩子插入
	public BinNode<T> insertAsRc(T e){
		return rChild = new BinNode<T>(this, (BinNode<T>)null, (BinNode<T>)null, e, 0);
	}
	
	// 直接后继
	public BinNode<T> succ() {	
		BinNode<T> binNode = this;
		if(rChild != null) {	// 若有右子树
			binNode = rChild;	// 直接后继是右子树中
			while(binNode.lChild != null) binNode = binNode.lChild;	// 最左的节点	
		}
		else {
			// 若没有右子树（可能this是右子树），while判断this是不是右子树
			// 情况1：父节点在右边，即this是左子树
			// 情况2： 父节点在坐标，即this是右子树
			// 一直向上走，直到（1）到一个左子树，那么左子树的父节点就是直接后继
			//				（2）到根节点，根节点的父节点为空，即没有直接后继
			while(binNode.parent != null && binNode == binNode.parent.rChild)
				binNode = binNode.parent;
			binNode = binNode.parent;
		}
		return binNode;
	}

}
