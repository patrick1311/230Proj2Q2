/*
Project Name: Sorting Algorithms (main.cpp)
Programmer Names: Justin Lin, Princeton Wong, Patrick Quach
Class: CSCI 230
Project Number: 1
Date: 3/28/2017
Project Description: This application runs various sorting algorithms and outputs their sort times to console and textfile.
*/

#include <cmath>	//pow
#include <iostream>	//cout
#include <string>	//string
#include <iomanip>	//setw formatting
#include <fstream>	//output textfile
#include <chrono>	//high-resolution clock
#include "bubsort.cpp"
#include "heapsort.cpp"
#include "heapsortO.cpp"
#include "inssort.cpp"
#include "mrgsort.cpp"
#include "mrgsortO.cpp"
#include "qsort.cpp"
#include "qsortop.cpp"
#include "radix.cpp"
#include "selsort.cpp"
#include "shellsort.cpp"
#include "shellsortO.cpp"

using namespace std;
using namespace std::chrono;

template<typename E> void fillArrAsc(E a[], int size);	//Fills array with values 0-n in ascending order
template<typename E> void initializeArr(E a[], int size);	//Initiate array with values 0
template<typename E> void copyArr(E a[], E b[], int size);	//Copies array b into array a
template<typename E> void shuffleArr(E a[], int size);	//Randomly shuffles an array
template<typename E> void calculateTimes(const int sizeStart, const int sizeEnd, int loopNumber, E insTimes[],
	E bubTimes[], E selTimes[], E shellTimes[], E shellOTimes[], E mrgTimes[], E mrgOTimes[],
	E qckTimes[], E qckOTimes[], E heapTimes[], E heapOTimes[], E rad4Times[], E rad8Times[]);
	//Calculates runtimes of sorting algorithms at various array sizes and stores the data inside arrays
template<typename E> void printTable(int sizeStart, int sizeEnd, E insTimes[], E bubTimes[], E selTimes[],
	E shellTimes[], E shellOTimes[], E mrgTimes[], E mrgOTimes[], E qckTimes[],
	E qckOTimes[], E heapTimes[], E heapOTimes[], E rad4Times[], E rad8Times[]);
	//Prints table of runtimes for different sorting algorithms at different sized arrays
template<typename E> double timeRecorder(void sort(E *, int), E *arr, int size);	//Records sorting algorithm runtime
template<typename E> void printSort(E arr[], int printStart, int printEnd, ofstream &textFile, std::string sortName);
	//Prints sort

int THRESHOLD1 = 4, THRESHOLD2 = 8;	//THRESHOLD1 used for radix sort/4; THRESHOLD2 used for radix sort/8
int pow2[9] = {1, 2, 4, 8, 16, 32, 64, 128, 256};	//Used for radix sort

int main() {
	srand((unsigned)time(0));
	const int sizeStart = 1, sizeEnd = 1;	//sizeStart and sizeEnd determine the range of array sizes to calculate runtimes for
	int loopNumber = 100000;	//Determines the number of times to loop to average the runtimes for sorts
	double insTimes[sizeEnd - sizeStart + 1], bubTimes[sizeEnd - sizeStart + 1], selTimes[sizeEnd - sizeStart + 1],
		shellTimes[sizeEnd - sizeStart + 1], shellOTimes[sizeEnd - sizeStart + 1], mrgTimes[sizeEnd - sizeStart + 1],
		mrgOTimes[sizeEnd - sizeStart + 1], qckTimes[sizeEnd - sizeStart + 1], qckOTimes[sizeEnd - sizeStart + 1],
		heapTimes[sizeEnd - sizeStart + 1], heapOTimes[sizeEnd - sizeStart + 1], rad4Times[sizeEnd - sizeStart + 1],
		rad8Times[sizeEnd - sizeStart + 1];
	calculateTimes(sizeStart, sizeEnd, loopNumber, insTimes,
		bubTimes, selTimes, shellTimes, shellOTimes, mrgTimes, mrgOTimes,
		qckTimes, qckOTimes, heapTimes, heapOTimes, rad4Times, rad8Times);
	printTable(sizeStart, sizeEnd, insTimes, bubTimes, selTimes,
		shellTimes, shellOTimes, mrgTimes, mrgOTimes, qckTimes,
		qckOTimes, heapTimes, heapOTimes, rad4Times, rad8Times);

	string buffer;
	cin >> buffer;	//Pause console after program finishes
	return 0;
}

template<typename E>
void fillArrAsc(E a[], int size) {	//Fills array with values 0-n in ascending order
	for (int i = 0; i < size; i++){
		a[i] = i;
	}
}

template<typename E>
void initializeArr(E a[], int size) {	//Initiates array with value 0
	for (int i = 0; i < size; i++) {
		a[i] = 0;
	}
}

template<typename E>
void copyArr(E a[], E b[], int size) {	//Copies array b into array a
	for (int i = 0; i < size; i++) {
		a[i] = b[i];
	}
}

template<typename E>
void shuffleArr(E a[], int size) {	//Randomly shuffles an array
	int num;
	for (int i = 0; i < size; i++){
		num = rand() % size;
		swap(a[i], a[num]);
	}
}

template<typename E>
void calculateTimes(const int sizeStart, const int sizeEnd, int loopNumber, E insTimes[], 
	E bubTimes[], E selTimes[], E shellTimes[], E shellOTimes[], E mrgTimes[], E mrgOTimes[], 
	E qckTimes[], E qckOTimes[], E heapTimes[], E heapOTimes[], E rad4Times[], E rad8Times[])
{	//Calculates runtimes of sorting algorithms at various array sizes and stores the data inside arrays
	initializeArr(insTimes, sizeEnd - sizeStart + 1);	//Initiate array with values 0
	initializeArr(bubTimes, sizeEnd - sizeStart + 1);
	initializeArr(selTimes, sizeEnd - sizeStart + 1);
	initializeArr(shellTimes, sizeEnd - sizeStart + 1);
	initializeArr(shellOTimes, sizeEnd - sizeStart + 1);
	initializeArr(mrgTimes, sizeEnd - sizeStart + 1);
	initializeArr(mrgOTimes, sizeEnd - sizeStart + 1);
	initializeArr(qckTimes, sizeEnd - sizeStart + 1);
	initializeArr(qckOTimes, sizeEnd - sizeStart + 1);
	initializeArr(heapTimes, sizeEnd - sizeStart + 1);
	initializeArr(heapOTimes, sizeEnd - sizeStart + 1);
	initializeArr(rad4Times, sizeEnd - sizeStart + 1);
	initializeArr(rad8Times, sizeEnd - sizeStart + 1);

	for (int i = sizeStart; i <= sizeEnd; i++)
	{
		int size = (int)pow(10.0, (double)i);
		int *arr = new int[size], *temp = new int[size];

		fillArrAsc(arr, size);	//Initialize array in ascending order

		for (int j = 0; j < loopNumber; j++)
		{
			shuffleArr(arr, size);	//Shuffle array randomly
			copyArr(temp, arr, size);	//Duplicate array to test the same random array across sorts

			insTimes[i - sizeStart] += timeRecorder(&inssort, arr, size);
			copyArr(arr, temp, size);	//Restore array to same random shuffle
			bubTimes[i - sizeStart] += timeRecorder(&bubsort, arr, size);
			copyArr(arr, temp, size);
			selTimes[i - sizeStart] += timeRecorder(&selsort, arr, size);
			copyArr(arr, temp, size);
			shellTimes[i - sizeStart] += timeRecorder(&shellsort, arr, size);
			copyArr(arr, temp, size);
			shellOTimes[i - sizeStart] += timeRecorder(&shellsortO, arr, size);
			copyArr(arr, temp, size);
			mrgTimes[i - sizeStart] += timeRecorder(&mrgsort, arr, size);
			copyArr(arr, temp, size);
			mrgOTimes[i - sizeStart] += timeRecorder(&mrgsortO, arr, size);
			copyArr(arr, temp, size);
			qckTimes[i - sizeStart] += timeRecorder(&qsort, arr, size);
			copyArr(arr, temp, size);
			qckOTimes[i - sizeStart] += timeRecorder(&qsortO, arr, size);
			copyArr(arr, temp, size);
			heapTimes[i - sizeStart] += timeRecorder(&heapsort, arr, size);
			copyArr(arr, temp, size);
			heapOTimes[i - sizeStart] += timeRecorder(&heapsortO, arr, size);
			copyArr(arr, temp, size);
			THRESHOLD1 = 4;
			rad4Times[i - sizeStart] += timeRecorder(&radixsort, arr, size);
			copyArr(arr, temp, size);
			THRESHOLD1 = 8;
			rad8Times[i - sizeStart] += timeRecorder(&radixsort, arr, size);
		}

		insTimes[i - sizeStart] /= loopNumber;	//Divide by loopNumber to average sort runtimes
		bubTimes[i - sizeStart] /= loopNumber;
		selTimes[i - sizeStart] /= loopNumber;
		shellTimes[i - sizeStart] /= loopNumber;
		shellOTimes[i - sizeStart] /= loopNumber;
		mrgTimes[i - sizeStart] /= loopNumber;
		mrgOTimes[i - sizeStart] /= loopNumber;
		qckTimes[i - sizeStart] /= loopNumber;
		qckOTimes[i - sizeStart] /= loopNumber;
		heapTimes[i - sizeStart] /= loopNumber;
		heapOTimes[i - sizeStart] /= loopNumber;
		rad4Times[i - sizeStart] /= loopNumber;
		rad8Times[i - sizeStart] /= loopNumber;

		delete [] arr, temp;
	}
}

template<typename E>
double timeRecorder(void sort(E *, int), E *arr, int size)
{	//Records sorting algorithm runtime
	high_resolution_clock::time_point t1, t2;
	double time;

	t1 = high_resolution_clock::now();
	sort(arr, size);
	t2 = high_resolution_clock::now();

	time = (double)duration_cast<nanoseconds>(t2 - t1).count() / 1000000;	//Divide by 1000000 to convert to miliseconds
	return time;
}

template<typename E>
void printTable(int sizeStart, int sizeEnd, E insTimes[], E bubTimes[], E selTimes[], 
	E shellTimes[], E shellOTimes[], E mrgTimes[], E mrgOTimes[], E qckTimes[],
	E qckOTimes[], E heapTimes[], E heapOTimes[], E rad4Times[], E rad8Times[])
{	//Prints table of runtimes for different sorting algorithms at different sized arrays to console and textfile
	ofstream textFile;
	textFile.open("SortingData.txt");

	std::cout << setw(10) << "Sort";
	textFile << "Sort";

	for (int i = sizeStart; i <= sizeEnd; i++)
	{
		std::cout << setw(12) << (int)pow(10, (double)(i));
		textFile << "\t" << (int)pow(10, (double)(i));
	}
	std::cout << endl;
	textFile << endl;

	printSort(insTimes, sizeStart, sizeEnd, textFile, "Insertion");
	printSort(bubTimes, sizeStart, sizeEnd, textFile, "Bubble");
	printSort(selTimes, sizeStart, sizeEnd, textFile, "Selection");
	printSort(shellTimes, sizeStart, sizeEnd, textFile, "Shell");
	printSort(shellOTimes, sizeStart, sizeEnd, textFile, "Shell/O");
	printSort(mrgTimes, sizeStart, sizeEnd, textFile, "Merge");
	printSort(mrgOTimes, sizeStart, sizeEnd, textFile, "Merge/O");
	printSort(qckTimes, sizeStart, sizeEnd, textFile, "Quick");
	printSort(qckOTimes, sizeStart, sizeEnd, textFile, "Quick/O");
	printSort(heapTimes, sizeStart, sizeEnd, textFile, "Heap");
	printSort(heapOTimes, sizeStart, sizeEnd, textFile, "Heap/O");
	printSort(rad4Times, sizeStart, sizeEnd, textFile, "Radix/4");
	printSort(rad8Times, sizeStart, sizeEnd, textFile, "Radix/8");

	textFile.close();
}

template<typename E>
void printSort(E arr[], int printStart, int printEnd, ofstream &textFile, std::string sortName)
{	//Prints sort to console and textfile
	std::cout << setw(10) << sortName;
	textFile << sortName;
	for (int i = printStart; i <= printEnd; i++)
	{
		std::cout << setw(12) << arr[i - printStart];
		textFile << "\t" << arr[i - printStart];
	}
	std::cout << endl;
	textFile << endl;
}