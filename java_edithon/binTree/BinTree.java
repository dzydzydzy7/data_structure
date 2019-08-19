package binTree;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;

public class BinTree<T> {
	protected int _size;	// 节点数
	protected BinNode<T> _root;	// 根节点

	// 更新x节点的高度
	protected int updateHeight(BinNode<T> x) {
		if (x.lChild != null && x.rChild != null)
			return x.height = 1 + Math.max(x.lChild.height, x.rChild.height);
		else if(x.lChild != null)
			return x.height = 1 + x.lChild.height;
		else if(x.rChild != null)
			return x.height = 1 + x.rChild.height;
		else return 1;
	}

	// 更新x以上节点的高度值
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

	// 返回大小
	public int size() {
		return _size;
	}

	// 判空
	public boolean isEmpty() {
		return _root == null;
	}

	// 返回根节点
	public BinNode<T> root() {
		return _root;
	}
	
	// 作为根节点插入
	public BinNode<T> insertAsRoot(T e) {
		_size = 1;
		return _root = new BinNode<T>(null, null, null, e, 0);
	}

	// 作为左孩子插入
	public BinNode<T> insertAsLC(BinNode<T> x, T e) {
		_size++;
		x.insertAsLc(e);
		updateHeightAbove(x);
		return x.lChild;
	}
	
	// 作为右孩子插入
	public BinNode<T> insertAsRC(BinNode<T> x, T e) {
		_size++;
		x.insertAsRc(e);
		updateHeightAbove(x);
		return x.rChild;
	}
	
	// 前序遍历，递归
	public void travPre_a(BinNode<T> x) {
		if (x == null)
			return;
		System.out.print("" + x.data + "\t");
		travPre_a(x.lChild);
		travPre_a(x.rChild);
	}
	
	// 前序遍历，迭代
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
			System.out.print("" + x.data + "\t");	// 输出
			s.push(x.rChild);
			x = x.lChild;
		}
	}
	
	// 前序遍历，迭代
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
	
	// 迭代（不使用辅助栈）
	public void travIn_c(BinNode<T> x) {
		boolean backtrack = false;	// 前一步是否刚从右子树回溯
		while(true) {
			if(!backtrack && x.lChild != null) {	// 没回溯且有左子树
				x = x.lChild;	// 继续向下不回溯
			}
			else {	// 没有左子树或刚刚回溯
				System.out.print("" + x.data + "\t");
				if(x.rChild != null) { 	// 没左子树有右子树
					x = x.rChild;	// 继续向下，不回溯
					backtrack = false;
				}
				else {
					if((x = x.succ()) == null) break;	// 如果没有左右子树，就直接转到直接后继，没有直接后继，中序遍历结束
					backtrack = true;	// 左右子树都空，回溯
				}
			}
		}
	}
	
	// 中序遍历，迭代法，不使用标记
	public void travIn_d(BinNode<T> x) {
		while(true) {
			if(x.lChild != null) x = x.lChild;	// 若有左子树，遍历左子树
			else {	// 若没有左子树（第一次到这里是到达最左节点）
				System.out.print("" + x.data + "\t");	// 输出最左节点
				while(x.rChild == null) {	// 如果没有右分支
					if((x = x.succ()) == null) return;	// 如果没有直接后继，中序遍历完毕
					else System.out.print("" + x.data + "\t");	// 如果有直接后继就是中序遍历的下一个
				}
				x = x.rChild;	// 若有右分支，转向右子树
			}
		}
	}
	
	// 中序遍历，递归
	public void travIn_e(BinNode<T> x) {
		if(x == null) return;
		travIn_e(x.lChild);
		System.out.print("" + x.data + "\t");
		travIn_e(x.rChild);
	}
	
	// 找到最左节点，沿途节点依次入栈
	public void gotoHLVFL(Stack<BinNode<T>> s)
	{
		while(s.peek() != null) {
			BinNode<T> x = s.peek();	// 当前节点为栈顶节点
			if(x.lChild != null) {	// 一直向左
				if(x.rChild != x) s.push(x.rChild); 	// 有右孩子就入栈
				s.push(x.lChild);	// 然后左孩子入栈
			}
			else s.push(x.rChild);	// 左边没有才向右
		}
		s.pop();
	}
	
	// 后续遍历，迭代法
	public void travPost_a(BinNode<T> x) {
		Stack<BinNode<T>> s = new Stack<BinNode<T>>();
		if(x != null) s.push(x);	// 根节点入栈
		while(!s.empty()) {
			if(s.peek() != x.parent)	// 若栈顶节点不是当前节点的父节点（必为右兄）
				gotoHLVFL(s);	// 找到右兄的最左
			x = s.pop();	// 出栈并输出
			System.out.print("" + x.data + "\t");
		}
	}
	
	// 后序遍历，递归法
	public void travPost_b(BinNode<T> x) {
		if(x == null) return;
		travPost_b(x.lChild);
		travPost_b(x.rChild);
		System.out.print("" + x.data + "\t");
	}
	
	// 层序遍历，使用队列
	public void travLevel(BinNode<T> x)
	{
		Queue<BinNode<T>> q = new LinkedList<BinNode<T>>();
		q.offer(x);	// 入列
		while(!q.isEmpty())
		{
			x = q.remove();
			System.out.print("" + x.data + "\t");
			if(x.lChild != null) q.offer(x.lChild);
			if(x.rChild != null) q.offer(x.rChild);
		}
	}
}
