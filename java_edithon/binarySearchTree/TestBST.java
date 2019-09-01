package binarySearchTree;

import binTree.BinNode;

public class TestBST {

	public static void main(String[] args) {
		Entry<Integer, Integer> e1 = new Entry<Integer,Integer>(3,3);
		Entry<Integer, Integer> e2 = new Entry<Integer, Integer>(3,4);
		System.out.print(e1.isLessThan(e2));
		System.out.print(e1.isGreaterThan(e2));
		System.out.print(e1.isEqual(e2));
		
		BST<Integer> bst = new BST<Integer>();
		bst.insertAsRoot(5);	// 插入树顶
		System.out.println(bst.isEmpty());	// 再判空
		
		// 初始化和测试树高
		BinNode<Integer> a = bst.insertAsLC(bst.root(), 3);
		BinNode<Integer> b1 = bst.insertAsLC(a, 1);
		BinNode<Integer> b2 = bst.insertAsRC(a, 4);
		bst.insertAsRC(bst.root(), 7);
		System.out.println(a.height);
		System.out.println(b1.height);
		System.out.println(b2.height);
		System.out.println(bst.root().height);
		
		System.out.println(bst.search(1).data);
		
		System.out.println(bst.search(6));
		bst.insert(6);
		System.out.println(bst.search(6).data);
		System.out.println(bst.root().height);
		
		bst.remove(7);
		bst.travIn_e(bst.root());
		System.out.println();
		bst.travLevel(bst.root());
		System.out.println();
		
		bst.insert(10);
		bst.travIn_e(bst.root());
		System.out.println();
		bst.travLevel(bst.root());
		System.out.println();
		
		bst.remove(5);
		bst.travIn_e(bst.root());
		System.out.println();
		bst.travLevel(bst.root());
		System.out.println();
		
		bst.remove(3);
		bst.travIn_e(bst.root());
		System.out.println();
		bst.travLevel(bst.root());
		System.out.println();
		
		bst.insert(7);
		bst.insert(8);
		bst.insert(9);
		bst.insert(11);
		bst.insert(18);
		bst.insert(15);
		bst.insert(20);
		bst.insert(5);
		bst.travIn_e(bst.root());
		System.out.println();
		bst.travLevel(bst.root());
		System.out.println();
		bst.travPre_a(bst.root());
		System.out.println();
		
		bst.remove(11);
		bst.travIn_e(bst.root());
		System.out.println();
		bst.travLevel(bst.root());
		System.out.println();
		bst.travPre_a(bst.root());
		System.out.println();
		bst.remove(9);
		bst.travIn_e(bst.root());
		System.out.println();
		bst.travLevel(bst.root());
		System.out.println();
		bst.travPre_a(bst.root());
		System.out.println();
	}

}
