import java.util.Scanner;


public class Main {
	public static void main(String args[]){
		Scanner in = new Scanner(System.in);
		
		LList list = new LList();
		int input = 0;
		int listOption = 0;
		
		
		for(int i = 1; i <= 10; i++)
			list.append(i);

		list.print();
		System.out.println();

		list.accessCount(8);
		list.print();
		list.accessCount(8);
		list.print();
		list.accessCount(8);
		list.print();
		list.accessCount(1);
		list.print();
		list.accessCount(1);
		list.print();
		list.accessCount(9);
		list.print();

		//System.out.println(list.getValue());
		//list.print();
		
		
		/*System.out.println();
		list.accessCount(10);
		list.print();
		/*
		while(input != -1){
			System.out.print("Access data: ");
			input = in.nextInt();
			list.accessCount(input);
		}

		/*
		while(option != 8){
			
			
			System.out.println("1. Append");
			System.out.println("2. Insert");
			System.out.println("3. Next");
			System.out.println("4. Get current position");
			System.out.println("5. Print list");
			System.out.println("6. Move to start");
			System.out.println("7. List length");
			System.out.println("8. Exit");
			System.out.print("Enter your choice: ");
			option = in.nextInt();
			
			switch(option){
				case 1:
					System.out.print("Enter data to append: ");
					list.append(in.nextInt());
					break;
				case 2:
					System.out.print("Enter data to insert: ");
					list.insert(in.nextInt());
					break;
				case 3:
					list.next();
					break;
				case 4: 
					System.out.println("Current position: " + list.getCurrPos());
					break;
				case 5:
					list.print();
					break;
				case 6:
					list.moveToStart();
					break;
				case 7:
					System.out.println("List size: " + list.getLength());
					break;
				case 8:
					System.out.println("Program Terminated!");
					break;
				default:
					System.out.println("Invalid! Choose again.");
					break;
			}
		}
		*/
		
		in.close();
	}
}
