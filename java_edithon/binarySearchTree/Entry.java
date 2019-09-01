package binarySearchTree;

public class Entry<K extends Comparable<? super K>, V>{
	private K key;
	private V value;

	Entry(K key, V value) {
		this.key = key;
		this.value = value;
	}

	Entry(Entry<K, V> e) {
		this.key = e.key;
		this.value = e.value;
	}

	boolean isLessThan(Entry<K, V> e) {
		return key.compareTo(e.key) < 0;
	}
	
	boolean isGreaterThan(Entry<K, V> e) {
		return key.compareTo(e.key) > 0;
	}
	
	boolean isEqual(Entry<K, V> e) {
		return key.compareTo(e.key) == 0;
	}
}
