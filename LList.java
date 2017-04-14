
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
		
		curr = head;
		
		System.out.printf("%-12s", "List: ");
		for(int i = 0; i < size; i++){
			System.out.print(curr.next.element + " ");
			curr = curr.next;
		}	
		System.out.println();
		
		curr = head;
		System.out.printf("%-12s", "Frequency: ");
		for(int i = 0; i < size; i++){
			System.out.print(curr.next.freq + " ");
			curr = curr.next;
		}
		System.out.println("\n");
	}
	
	public int getValue(){
		return curr.next.element;
	}
	
	public int getComp(){
		return compCount;
	}
	
	public int getLength(){
		return size;
	}
	
	//Count self-organizing list
	public void accessCount(int data){
		
		curr = head;
		for(int i = 0; i < getLength(); i++){
			compCount++;
			if(data == curr.next.element){
				curr.next.freq++;
				break;
			}
			curr = curr.next;	
		}
		
		ListNode t = curr.next;		//store the node that needed to move
		ListNode t2 = curr;
		
		curr = head;
		for(int i = 0; i < getLength(); i++){
			
			//check if its itself
			if(t == curr.next)
				break;
			
			//check where to insert based on frequency
			if(t.freq > curr.next.freq){
				t2.next = t.next;
				t.next = curr.next;
				curr.next = t;
				break;
			}
			curr = curr.next;
		}
	}
	
	//Move to front self-organizing list
	public void accessMTF(int data){
		
		curr = head;
		ListNode t;
		for(int i = 0; i < getLength(); i++){
			compCount++;
			if(data == curr.next.element){
				t = curr.next;
				curr.next = t.next;
				t.next = head.next;
				head.next = t;
				break;
			}
			curr = curr.next;
		}
	}
	
	//Transpose self-organizing list
	public void accessTranspose(int data){
		
		ListNode temp;
		curr = head;
		for(int i = 0; i < getLength(); i++){
			compCount++;
			if(data == curr.next.element){
				if(curr == head) 	//no swap if access first node
					break;
				
				temp = curr.next;
				curr.next = temp.next;
				temp.next = curr;
				
				ListNode temp2 = head;
				while(temp2.next != curr)
					temp2 = temp2.next;
				temp2.next = temp;
				break;
			}	
			curr = curr.next;
		}
	}
	
}
