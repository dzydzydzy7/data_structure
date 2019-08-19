package binTree;

public class BinNode<T> {
	public BinNode<T> parent;
	public BinNode<T> lChild;
	public BinNode<T> rChild;
	
	public T data;
	public int height;	// �ڵ�߶�
	
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
	
	// �����Ľڵ���
	public int size() {
		int s = 1;
		if(lChild != null) s += lChild.size();
		if(rChild != null) s += rChild.size();
		return s;
	}
	
	// ��Ϊ���Ӳ���
	public BinNode<T> insertAsLc(T e){
		return lChild = new BinNode<T>(this, (BinNode<T>)null, (BinNode<T>)null, e, 0);
	}
	
	// ��Ϊ�Һ��Ӳ���
	public BinNode<T> insertAsRc(T e){
		return rChild = new BinNode<T>(this, (BinNode<T>)null, (BinNode<T>)null, e, 0);
	}
	
	// ֱ�Ӻ��
	public BinNode<T> succ() {	
		BinNode<T> binNode = this;
		if(rChild != null) {	// ����������
			binNode = rChild;	// ֱ�Ӻ������������
			while(binNode.lChild != null) binNode = binNode.lChild;	// ����Ľڵ�	
		}
		else {
			// ��û��������������this������������while�ж�this�ǲ���������
			// ���1�����ڵ����ұߣ���this��������
			// ���2�� ���ڵ������꣬��this��������
			// һֱ�����ߣ�ֱ����1����һ������������ô�������ĸ��ڵ����ֱ�Ӻ��
			//				��2�������ڵ㣬���ڵ�ĸ��ڵ�Ϊ�գ���û��ֱ�Ӻ��
			while(binNode.parent != null && binNode == binNode.parent.rChild)
				binNode = binNode.parent;
			binNode = binNode.parent;
		}
		return binNode;
	}

}
