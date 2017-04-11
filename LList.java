
public class LList extends ListNode{
	
	private ListNode head;
	private ListNode tail;
	private ListNode curr;
	private int size;
	
	public LList(){
		head = tail = curr = new ListNode();
		size = 0;
	}
	
	public void moveToStart(){
		curr = head;
	}
	
	public void next(){
		if(curr == tail){
			curr = head;
		}
		else{
			curr = curr.next;
		}
	}
	
	public void append(int data){
		tail.next = new ListNode(data, null);
		tail = tail.next;
		size++;
	}
	
	public void insert(int data){
		curr.next = new ListNode(data, curr.next);
		if(tail == curr){
			tail = curr.next;
		}
		size++;
	}
	
	public void print(){
		ListNode temp = curr;	//keep curr
		
		curr = head;
		for(int i = 0; i < size; i++){
			System.out.print(curr.next.element + " ");
			curr = curr.next;
		}	
		System.out.println();
		
		curr = temp;	//restore curr
	}
	
	public int getLength(){
		return size;
	}
}
