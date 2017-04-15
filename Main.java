/*
 * Self organizing list: Count, Move to front, Transpose
 */
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Main {
	public static void main(String args[]) throws FileNotFoundException{
		Scanner in = new Scanner(new File("src/text.txt"));
		
		LList<String> list = new LList<String>();
		String data;
		double time = System.nanoTime();
		
		
		while(in.hasNext()){
			
			data = in.next();
			
			if(!list.isInList(data)){
				list.append(data);
				list.accessCount(data);	//use accessCount, accessMTF, accessTranspose
			}
			else
				list.accessCount(data);
		}
		
		time = System.nanoTime() - time;
		list.print();
		
		System.out.println("Comparison = " + list.getComp());
		System.out.println("Run Time: " + time + " nanoseconds");
		in.close();
	}
}
