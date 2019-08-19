package binTree;

public class TestBinTree {

	public static void main(String[] args) {
		BinTree<Integer> binTree = new BinTree<Integer>();
		System.out.println(binTree.isEmpty());	// 判空
		
		binTree.insertAsRoot(3);	// 插入树顶
		System.out.println(binTree.isEmpty());	// 再判空
		
		// 初始化和测试树高
		BinNode<Integer> a = binTree.insertAsLC(binTree.root(), 4);
		BinNode<Integer> b1 = binTree.insertAsLC(a, 6);
		BinNode<Integer> b2 = binTree.insertAsRC(a, 7);
		binTree.insertAsRC(binTree.root(), 5);
		System.out.println(a.height);
		System.out.println(b1.height);
		System.out.println(b2.height);
		System.out.println(binTree.root().height);
		
		// 前序遍历
		binTree.travPre_a(binTree.root());
		System.out.println();
		binTree.travPre_b(binTree.root());
		System.out.println();
		binTree.travPre_c(binTree.root());
		System.out.println();
		
		// 中序遍历
		binTree.travIn_a(binTree.root());
		System.out.println();
		binTree.travIn_b(binTree.root());
		System.out.println();
		binTree.travIn_c(binTree.root());
		System.out.println();
		binTree.travIn_d(binTree.root());
		System.out.println();
		binTree.travIn_c(binTree.root());
		System.out.println();
		
		// 后序遍历
		binTree.travPost_a(binTree.root());
		System.out.println();
		binTree.travPost_b(binTree.root());
		System.out.println();
		
		// 层次遍历
		binTree.travLevel(binTree.root());
		System.out.println();
	}

}
