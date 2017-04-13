
public class LList{
	
	private ListNode head;
	private ListNode tail;
	private ListNode curr;
	private int size;
	private int compCount = 0;
	
	public LList(){
		head = tail = curr = new ListNode();
		size = 0;
	}
	
	public void moveToStart(){
		curr = head;
	}
	
	public int getCurrPos(){
		ListNode temp = head;
		int pos = 0;
		for(pos = 0; temp != curr; pos++){
			temp = temp.next;
		}
		return pos;
	}
	
	public void next(){
		if(curr == tail){
			curr = head;
		}
		else{
			curr = curr.next;
		}
	}
	
	public void prev(){
		if(curr == head)
			return;
		
		ListNode temp = head;
		while(temp.next != curr)
			temp = temp.next;
		
		curr = temp;
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
		
		curr = head;
		for(int i = 0; i < size; i++){
			System.out.print(curr.next.freq + " ");
			curr = curr.next;
		}
		System.out.println();
		
		curr = temp;	//restore curr
	}
	
	public int getValue(){
		return curr.next.element;
	}
	
	public int getLength(){
		return size;
	}
	
	public void accessCount(int data){
		ListNode temp = curr;	//keep curr
		
		curr = head;
		for(int i = 0; i < getLength(); i++){
			compCount++;
			if(data == curr.next.element){
				curr.next.freq++;
				break;
			}
			curr = curr.next;	
		}
		//System.out.println(getValue());
		
		ListNode t = curr.next;	//store the node that needed to move
		
		ListNode t2 = curr;
		
		curr = head;
		
		for(int i = 0; i < getLength(); i++){
			if(t == curr.next)
				break;
			if(t.freq > curr.next.freq){
				//insert
				t2.next = t.next;
				t.next = curr.next;
				curr.next = t;
				break;
			}
			curr = curr.next;
		}
		
		
		
		curr = temp;	//restore curr
	}
	
}
