
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
			//curr = curr.next;
			if(data == curr.next.element){
				curr.freq++;
			}
			curr = curr.next;
			compCount++;
		}
		prev();
		
		
		ListNode temp2 = head;	//reset to starting point
		ListNode temp3 = curr.next;
		
		for(int i = 0; i < getLength(); i++){
			temp2 = temp2.next;
			if(temp2.next.freq < temp2.freq){
				
				curr.next = curr.next.next;
				temp3.next = temp2.next;
				temp2.next = temp3;
			}
		}
		
		curr = temp;	//restore curr
	}
}
