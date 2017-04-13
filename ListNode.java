
public class ListNode {
	
	public ListNode next;
	public int element;
	public int freq;
	
	public ListNode(){
		next = null;
		freq = 0;
	}
	
	public ListNode(int e, ListNode nextval){
		element = e;
		next = nextval;
		freq = 0;
	}
	
}
