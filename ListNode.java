
public class ListNode<E> {
	
	public ListNode<E> next;
	public E element;
	public int freq;
	
	public ListNode(){
		next = null;
		freq = 0;
	}
	
	public ListNode(E e, ListNode<E> nextval){
		element = e;
		next = nextval;
		freq = 0;
	}
	
}
