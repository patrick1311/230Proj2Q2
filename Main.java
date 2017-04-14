/*
 * Self organizing list: Count, Move to front, Transpose
 */

public class Main {
	public static void main(String args[]){
		
		LList listCount = new LList();
		LList listMTF = new LList();
		LList listTranspose = new LList();
		
		for(int i = 0; i < 10; i++)
			listTranspose.append(i);

		listTranspose.print();

		listTranspose.accessTranspose(8);
		listTranspose.print();
		listTranspose.accessTranspose(8);
		listTranspose.print();
		listTranspose.accessTranspose(8);
		listTranspose.print();
		listTranspose.accessTranspose(0);
		listTranspose.print();
		listTranspose.accessTranspose(4);
		listTranspose.print();
		System.out.println("Comparison = " + listTranspose.getComp());
	}
}
