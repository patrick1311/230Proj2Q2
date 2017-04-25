/*
 * Self organizing list: Count, Move to front, Transpose
 */

import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class Main {
	public static void main(String args[]) throws IOException{	
		Random rand = new Random();
		File file = new File("src/text.txt");
		FileWriter out = new FileWriter(file);
		FileReader in = new FileReader(file);
		
		LList<Character> countList = new LList<Character>();
		LList<Character> MTFList = new LList<Character>();
		LList<Character> transposeList = new LList<Character>();
		char[] arr = new char[100];

		for(int i = 0; i < arr.length; i++){
			arr[i] = (char) (rand.nextInt(26) + 65);	//generate random A-Z
			out.write(arr[i]);
		}
		
		//read text into array 
		in.read(arr);	
		
		//Start and warm up JIT and JVM to measure run time more accurately
		warmUp(arr);
		System.out.println("Above method is called to warm up JVM timer!\n");
		
		//3 types of self-organizing lists
		count(countList, arr);
		MTF(MTFList, arr);
		transpose(transposeList, arr);
		
		out.close();
		in.close();
	}
	
	public static void warmUp(char[] a){
		
		long time = System.nanoTime();
		LList<Character> test = new LList<Character>();

		for(int i = 0; i < a.length; i++){		
			if(!test.isInList(a[i]))
				test.append(a[i]);
			test.accessCount(a[i]);
		}
		time = System.nanoTime() - time;
		System.out.println("Warm up time: " + time + " nanoseconds");
	}
	
	public static void count(LList<Character> list, char[] a){
		System.out.println("-----Count-----");
		long start = System.nanoTime();	//start elapsed time
		
		for(int i = 0; i < a.length; i++){		
			if(!list.isInList(a[i]))
				list.append(a[i]);
			list.accessCount(a[i]);
		}
		long end = System.nanoTime();
		long time = end - start;
		
		list.printList();
		list.printFreq();
		System.out.println("Comparison = " + list.getComp());
		System.out.println("Run Time: " + time + " nanoseconds\n");
	}
	
	public static void transpose(LList<Character> list, char[] a){
		System.out.println("-----Transpose-----");
		long start = System.nanoTime();	//start elapsed time
		
		for(int i = 0; i < a.length; i++){		
			if(!list.isInList(a[i]))
				list.append(a[i]);
			list.accessTranspose(a[i]);
		}
		long end = System.nanoTime();
		long time = end - start;
		
		list.printList();
		System.out.println("Comparison = " + list.getComp());
		System.out.println("Run Time: " + time + " nanoseconds\n");
	}
	
	public static void MTF(LList<Character> list, char[] a){
		System.out.println("-----MTF-----");
		long start = System.nanoTime();	//start elapsed time
		
		for(int i = 0; i < a.length; i++){		
			if(!list.isInList(a[i]))
				list.append(a[i]);
			list.accessMTF(a[i]);
		}
		long end = System.nanoTime();
		long time = end - start;
		
		list.printList();
		System.out.println("Comparison = " + list.getComp());
		System.out.println("Run Time: " + time + " nanoseconds\n");
	}
}
