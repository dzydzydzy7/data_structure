package binTree;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;

public class BinTree<T> {
	protected int _size;	// �ڵ���
	protected BinNode<T> _root;	// ���ڵ�

	// ����x�ڵ�ĸ߶�
	protected int updateHeight(BinNode<T> x) {
		if (x.lChild != null && x.rChild != null)
			return x.height = 1 + Math.max(x.lChild.height, x.rChild.height);
		else if(x.lChild != null)
			return x.height = 1 + x.lChild.height;
		else if(x.rChild != null)
			return x.height = 1 + x.rChild.height;
		else return 1;
	}

	// ����x���Ͻڵ�ĸ߶�ֵ
	protected void updateHeightAbove(BinNode<T> x) {
		while (x != null) {
			updateHeight(x);
			x = x.parent;
		}
	}

	public BinTree() {
		this._size = 0;
		this._root = null;
	}

	public BinTree(int size, BinNode<T> root) {
		this._size = size;
		this._root = root;
	}

	// ���ش�С
	public int size() {
		return _size;
	}

	// �п�
	public boolean isEmpty() {
		return _root == null;
	}

	// ���ظ��ڵ�
	public BinNode<T> root() {
		return _root;
	}
	
	// ��Ϊ���ڵ����
	public BinNode<T> insertAsRoot(T e) {
		_size = 1;
		return _root = new BinNode<T>(null, null, null, e, 0);
	}

	// ��Ϊ���Ӳ���
	public BinNode<T> insertAsLC(BinNode<T> x, T e) {
		_size++;
		x.insertAsLc(e);
		updateHeightAbove(x);
		return x.lChild;
	}
	
	// ��Ϊ�Һ��Ӳ���
	public BinNode<T> insertAsRC(BinNode<T> x, T e) {
		_size++;
		x.insertAsRc(e);
		updateHeightAbove(x);
		return x.rChild;
	}
	
	// ǰ��������ݹ�
	public void travPre_a(BinNode<T> x) {
		if (x == null)
			return;
		System.out.print("" + x.data + "\t");
		travPre_a(x.lChild);
		travPre_a(x.rChild);
	}
	
	// ǰ�����������
	public void travPre_b(BinNode<T> x) {
		Stack<BinNode<T>> s = new Stack<BinNode<T>>();
		if(x!=null) s.push(x);
		while(!s.empty()) {
			x = s.pop();
			System.out.print("" + x.data + "\t");
			if(x.rChild != null) s.push(x.rChild);
			if(x.lChild != null) s.push(x.lChild);
		}
	}
		
	public void visitAlongLeftBranch(BinNode<T> x, Stack<BinNode<T>> s) {
		while(x != null) {
			System.out.print("" + x.data + "\t");	// ���
			s.push(x.rChild);
			x = x.lChild;
		}
	}
	
	// ǰ�����������
	public void travPre_c(BinNode<T> x)
	{
		Stack<BinNode<T>> s = new Stack<BinNode<T>>();
		while(true) {
			visitAlongLeftBranch(x, s);
			if(s.empty()) break;
			x = s.pop();
		}
	}
	
	public void visitAlongLeftBranch_In(BinNode<T> x, Stack<BinNode<T>> s) {
		while(x != null) {
			s.push(x);
			x = x.lChild;
		}
	}
	
	public void travIn_a(BinNode<T> x) {
		Stack<BinNode<T>> s = new Stack<BinNode<T>>();
		while(true) {
			visitAlongLeftBranch_In(x, s);
			if(s.empty()) break;
			x = s.pop();
			System.out.print("" + x.data + "\t");
			x = x.rChild;
		}
	}
	
	public void travIn_b(BinNode<T> x) {
		Stack<BinNode<T>> s = new Stack<BinNode<T>>();
		while(true) {
			if(x != null) {
				s.push(x);
				x = x.lChild;
			}
			else if(!s.empty()) {
				x = s.pop();
				System.out.print("" + x.data + "\t");
				x = x.rChild;
			}
			else break;
		}
	}
	
	// ��������ʹ�ø���ջ��
	public void travIn_c(BinNode<T> x) {
		boolean backtrack = false;	// ǰһ���Ƿ�մ�����������
		while(true) {
			if(!backtrack && x.lChild != null) {	// û��������������
				x = x.lChild;	// �������²�����
			}
			else {	// û����������ոջ���
				System.out.print("" + x.data + "\t");
				if(x.rChild != null) { 	// û��������������
					x = x.rChild;	// �������£�������
					backtrack = false;
				}
				else {
					if((x = x.succ()) == null) break;	// ���û��������������ֱ��ת��ֱ�Ӻ�̣�û��ֱ�Ӻ�̣������������
					backtrack = true;	// �����������գ�����
				}
			}
		}
	}
	
	// �������������������ʹ�ñ��
	public void travIn_d(BinNode<T> x) {
		while(true) {
			if(x.lChild != null) x = x.lChild;	// ����������������������
			else {	// ��û������������һ�ε������ǵ�������ڵ㣩
				System.out.print("" + x.data + "\t");	// �������ڵ�
				while(x.rChild == null) {	// ���û���ҷ�֧
					if((x = x.succ()) == null) return;	// ���û��ֱ�Ӻ�̣�����������
					else System.out.print("" + x.data + "\t");	// �����ֱ�Ӻ�̾��������������һ��
				}
				x = x.rChild;	// �����ҷ�֧��ת��������
			}
		}
	}
	
	// ����������ݹ�
	public void travIn_e(BinNode<T> x) {
		if(x == null) return;
		travIn_e(x.lChild);
		System.out.print("" + x.data + "\t");
		travIn_e(x.rChild);
	}
	
	// �ҵ�����ڵ㣬��;�ڵ�������ջ
	public void gotoHLVFL(Stack<BinNode<T>> s)
	{
		while(s.peek() != null) {
			BinNode<T> x = s.peek();	// ��ǰ�ڵ�Ϊջ���ڵ�
			if(x.lChild != null) {	// һֱ����
				if(x.rChild != x) s.push(x.rChild); 	// ���Һ��Ӿ���ջ
				s.push(x.lChild);	// Ȼ��������ջ
			}
			else s.push(x.rChild);	// ���û�в�����
		}
		s.pop();
	}
	
	// ����������������
	public void travPost_a(BinNode<T> x) {
		Stack<BinNode<T>> s = new Stack<BinNode<T>>();
		if(x != null) s.push(x);	// ���ڵ���ջ
		while(!s.empty()) {
			if(s.peek() != x.parent)	// ��ջ���ڵ㲻�ǵ�ǰ�ڵ�ĸ��ڵ㣨��Ϊ���֣�
				gotoHLVFL(s);	// �ҵ����ֵ�����
			x = s.pop();	// ��ջ�����
			System.out.print("" + x.data + "\t");
		}
	}
	
	// ����������ݹ鷨
	public void travPost_b(BinNode<T> x) {
		if(x == null) return;
		travPost_b(x.lChild);
		travPost_b(x.rChild);
		System.out.print("" + x.data + "\t");
	}
	
	// ���������ʹ�ö���
	public void travLevel(BinNode<T> x)
	{
		Queue<BinNode<T>> q = new LinkedList<BinNode<T>>();
		q.offer(x);	// ����
		while(!q.isEmpty())
		{
			x = q.remove();
			System.out.print("" + x.data + "\t");
			if(x.lChild != null) q.offer(x.lChild);
			if(x.rChild != null) q.offer(x.rChild);
		}
	}
}
