
public class LList<E>{
	
	private ListNode<E> head;
	private ListNode<E> tail;
	private ListNode<E> curr;
	private int size;
	private int compCount = 0;
	
	public LList(){
		head = tail = curr = new ListNode<E>();
		size = 0;
	}
	
	public void moveToStart(){
		curr = head;
	}
	
	public int getCurrPos(){
		ListNode<E> temp = head;
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
		
		ListNode<E> temp = head;
		while(temp.next != curr)
			temp = temp.next;
		
		curr = temp;
	}
	
	public void append(E data){
		tail.next = new ListNode<E>(data, null);
		tail = tail.next;
		size++;
	}
	
	public void insert(E data){
		curr.next = new ListNode<E>(data, curr.next);
		if(tail == curr){
			tail = curr.next;
		}
		size++;
	}
	
	public void resetTail(){
		while(tail.next != null)
			tail = tail.next;
	}
	
	public void printList(){
		
		curr = head;
		System.out.printf("%-12s", "Final list: ");
		for(int i = 0; i < size; i++){
			System.out.print(curr.next.element + " ");
			curr = curr.next;
		}	
		System.out.println();	
	}
	
	public void printFreq(){

		curr = head;
		System.out.printf("%-12s", "Frequency: ");
		for(int i = 0; i < size; i++){
			System.out.print(curr.next.freq + " ");
			curr = curr.next;
		}
		System.out.println();
	}
	
	public E getValue(){
		return curr.next.element;
	}
	
	public int getComp(){
		return compCount;
	}
	
	public int getLength(){
		return size;
	}
	
	public boolean isInList(E data){
		curr = head;
		while(curr.next != null){
			
			if(curr.next.element.equals(data))
				return true;
			
			curr = curr.next;
		}
		return false;
	}
	
	//Count self-organizing list
	public void accessCount(E data){
				
		curr = head;
		for(int i = 0; i < getLength(); i++){
			compCount++;
			if(data.equals(curr.next.element)){
				curr.next.freq++;
				break;
			}
			curr = curr.next;	
		}
		
		ListNode<E> t = curr.next;		//store the node that needed to move
		ListNode<E> t2 = curr;
		
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
		
		resetTail();
	}
	
	//Move to front self-organizing list
	public void accessMTF(E data){
		
		curr = head;
		ListNode<E> t;
		for(int i = 0; i < getLength(); i++){
			compCount++;
			if(data.equals(curr.next.element)){
				t = curr.next;
				curr.next = t.next;
				t.next = head.next;
				head.next = t;
				break;
			}
			curr = curr.next;
		}
		
		resetTail();
	}
	
	//Transpose self-organizing list
	public void accessTranspose(E data){
		
		ListNode<E> temp;
		curr = head;
		for(int i = 0; i < getLength(); i++){
			compCount++;
			if(data.equals(curr.next.element)){
				if(curr == head) 	//no swap if access first node
					break;
				
				//swap or transpose with prev node
				temp = curr.next;
				curr.next = temp.next;
				temp.next = curr;
				
				ListNode<E> temp2 = head;
				while(temp2.next != curr)
					temp2 = temp2.next;
				temp2.next = temp;
				break;
			}	
			curr = curr.next;
		}
		
		resetTail();
	}

}
