package binTree;

public class TestBinTree {

	public static void main(String[] args) {
		BinTree<Integer> binTree = new BinTree<Integer>();
		System.out.println(binTree.isEmpty());	// �п�
		
		binTree.insertAsRoot(3);	// ��������
		System.out.println(binTree.isEmpty());	// ���п�
		
		// ��ʼ���Ͳ�������
		BinNode<Integer> a = binTree.insertAsLC(binTree.root(), 4);
		BinNode<Integer> b1 = binTree.insertAsLC(a, 6);
		BinNode<Integer> b2 = binTree.insertAsRC(a, 7);
		binTree.insertAsRC(binTree.root(), 5);
		System.out.println(a.height);
		System.out.println(b1.height);
		System.out.println(b2.height);
		System.out.println(binTree.root().height);
		
		// ǰ�����
		binTree.travPre_a(binTree.root());
		System.out.println();
		binTree.travPre_b(binTree.root());
		System.out.println();
		binTree.travPre_c(binTree.root());
		System.out.println();
		
		// �������
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
		
		// �������
		binTree.travPost_a(binTree.root());
		System.out.println();
		binTree.travPost_b(binTree.root());
		System.out.println();
		
		// ��α���
		binTree.travLevel(binTree.root());
		System.out.println();
	}

}
