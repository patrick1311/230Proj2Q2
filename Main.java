/*
 * Self organizing list: Count, Move to front, Transpose
 */

import java.util.Scanner;


public class Main {
	public static void main(String args[]){
		Scanner in = new Scanner(System.in);
		
		LList list = new LList();
	
		for(int i = 0; i < 10; i++)
			list.append(i);

		list.print();

		list.accessTranspose(8);
		list.print();
		list.accessTranspose(8);
		list.print();
		list.accessTranspose(8);
		list.print();
		list.accessTranspose(0);
		list.print();
		list.accessTranspose(4);
		list.print();
		in.close();
	}
}
