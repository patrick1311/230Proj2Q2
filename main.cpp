//To do list: <-----------------LOOK HERE!
//1.get rid of global variables, (make class?)
//2.determine numRuns for multimerge
//3.test on larger sized buffers & heap; determine buffer/heap size
//4.answer prompt questions 
//5.clean up code: find more efficient/better methods, make code modular if possible, make coding style consistent, split functions into separate files? etc.
//6.write comments
//7.make beautiful graphs
//8.find fourth group member

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>	//time
#include <limits>	//GoToLine
#include "heap.h"
#include "Comp.cpp"
#include "qsortop.cpp"

int THRESHOLD2 = 8;
bool done = false;
int eofLine = 7;

bool isEmptyArr(std::string *arr, int size);
void genRandFile(std::string fileName, int lines);
std::streamoff readData(std::string fileName, std::string *inBuff, std::streamoff start, int size);
template<typename E> void printArr(E a[], int size);
template<typename E> void repSel(std::string inFile, std::string outFile, heap<E, Comp<E>>* minHeap, std::streamoff start, int buffSize);
void clearData(std::string fileName);
template<typename E> void writeData(std::string fileName, E output, int size);
template<typename E> void writeData(std::string fileName, E *outBuff, int size);
void multiMrg(std::string inFile, std::string outFile, int buffSize, int numRuns);
std::fstream& goToLine(std::fstream& file, int num);
int minIndex(std::string *arr, int size);	//Returns index of smallest element in array
template<typename E> void initializeArr(E a[], int size);	//Initiates array with value 0

int main()
{
	srand((unsigned)time(0));
	int bufferSize = eofLine, heapSize = 7;
	std::streamoff start;
	std::string inputFile = "RandomData.txt", preMrgFile = "PreMerge.txt", mergeFile = "SortedData.txt";

	std::string *heapArr = new std::string[heapSize];
	clearData(preMrgFile);	//Clear output file
	clearData(mergeFile);	//Clear output file
	genRandFile(inputFile, 23);	//Generate input file
	start = readData(inputFile, heapArr, 0, heapSize);	//Read data into heap array
	heap<std::string, Comp<std::string>>* minHeap = new heap<std::string, Comp<std::string>>(heapArr, heapSize, heapSize);
		std::cout << "heap___________________________________" << std::endl;	//Delete when done testing
		printArr(heapArr, heapSize);											//Delete when done testing
		repSel<std::string>(inputFile, preMrgFile, minHeap, start, bufferSize);
		qsortO(heapArr, heapSize);
		std::cout << "heap___________________________________" << std::endl;	//Delete when done testing
		printArr(heapArr, heapSize);											//Delete when done testing
	writeData(preMrgFile, heapArr, heapSize);	//Write array to output file
	multiMrg(preMrgFile, mergeFile, bufferSize, 3);	//Merge output buffers together
	std::string wait;
	std::cin >> wait;	//Pause console after program finishes
	return 0;
}

void genRandFile(std::string fileName, int lines)
{	//Generates random character text file
	std::ofstream ofs;
	ofs.open(fileName);

	int randLines = lines;//(rand() % 100) + 60;
	int randLength, maxLength = 20;
	char randChar;
	for (int i = 0; i < randLines; i++)
	{
		randLength = (rand() % maxLength) + 1;
		for (int j = 0; j < randLength; j++)
		{
			randChar = (rand() % 26) + 'A';
			ofs << randChar;
		}
		ofs << std::endl;
	}
	ofs.close();
}

std::streamoff readData(std::string fileName, std::string *inBuff, std::streamoff start, int size)
{
	std::streamoff getPos;
	std::ifstream ifs(fileName);

	if (ifs.is_open())
	{
		ifs.seekg(start);
		for (int i = 0; i < size; i++)
		{
			if (ifs.eof())
			{
				eofLine = i - 1;	//Record line number of eof
				done = true;
				break;	//Stop recording into input buffer
			}
			getline(ifs, inBuff[i]);
		}
	}
	getPos = ifs.tellg();
	ifs.close();

	return getPos;
}

void clearData(std::string fileName)
{	//Clears file
	std::ofstream ofs(fileName, std::ios::out | std::ios::trunc);
	ofs.close();
}

template<typename E>
void writeData(std::string fileName, E output, int size)
{	//Writes data to file
	std::ofstream ofs(fileName, std::ios::out | std::ios::app);

	if (ofs.is_open())
	{
		ofs << output << std::endl;
	}
	ofs.close();
}

template<typename E>
void writeData(std::string fileName, E *outBuff, int size)
{	//Writes array to file
	std::ofstream ofs(fileName, std::ios::out | std::ios::app);

	if (ofs.is_open())
	{
		for (int i = 0; i < size; i++)
		{
			ofs << outBuff[i] << std::endl;
		}
	}
	ofs.close();
}

template<typename E>
void printArr(E a[], int size) {	//Prints an array
	for (int i = 0; i < size; i++) {
		std::cout << a[i] << std::endl;
	}
}

template<typename E>
void repSel(std::string inFile, std::string outFile, heap<E, Comp<E>>* minHeap, std::streamoff start, int buffSize)
{
	E *inBuff = new E[buffSize];
	E *outBuff = new E[buffSize];
	int heapSize = minHeap->size();

	do//for (int i = 0; i < 2; i++)
	{
		start = readData(inFile, inBuff, start, buffSize);
		for (int j = 0; j < eofLine; j++)
		{
			if (minHeap->size() == 0)	//If heap size is 0, rebuild heap
			{
				minHeap->setHeapSize(heapSize);
				minHeap->buildHeap();
			}

			outBuff[j] = minHeap->getVal(0);	//Send root to heap buffer
			minHeap->setVal(0, inBuff[j]);	//Set root to input buffer value
			if (inBuff[j] > outBuff[j])
			{
				minHeap->siftdown(0);	//Siftdown root
			}
			else
			{
				minHeap->removefirst();	//Else place root at end and reduce heap size
			}
		}
		writeData(outFile, outBuff, eofLine);	//Write output buffer to file
		minHeap->setHeapSize(heapSize);	//Rebuild heap
		minHeap->buildHeap();
			std::cout << "in___________________________________" << std::endl;		  //Delete when done testing
			printArr(inBuff, buffSize);												  //Delete when done testing
			std::cout << "out___________________________________" << std::endl;		  //Delete when done testing
			printArr(outBuff, eofLine);												  //Delete when done testing
	} while (!done);
	delete[] inBuff;
	delete[] outBuff;
}

void multiMrg(std::string inFile, std::string outFile, int buffSize, int numRuns)	//Temporarily using quicksort for testing
{
	std::fstream ifs(inFile);
	std::ofstream ofs(outFile);
	int size = numRuns + 1;
	int minI;
	std::string *runBuff = new std::string[size];
	int *runStart = new int[size];

	initializeArr(runStart, size);
	if (ifs.is_open() && ofs.is_open())
	{
		do
		{
				std::cout << "_____________________" << std::endl;		//Delete when done testing
			for (int j = 0; j < size; j++)
			{
				goToLine(ifs, buffSize * j + 1 + runStart[j]);
				if (runStart[j] == 0 || runBuff[j] != "")
				{	//If start of run or run is not empty then ???
					ifs >> runBuff[j];
				}
					std::cout << runBuff[j] << std::endl;		//Delete when done testing
			}
			minI = minIndex(runBuff, size);	//Find smallest run buffer value of all runs
			ofs << runBuff[minI] << std::endl;	//Write smallest run buffer value to textfile
			runStart[minI]++;	//Move to next element in run
			if (runStart[minI] == buffSize || (minI == (size - 1) && runStart[minI] == eofLine))
			{	//If run is finished then run buffer value is an empty string
				runBuff[minI] = "";
			}
		} while (!isEmptyArr(runBuff, size));	//Continue looping until all runs are finished
	}
	ofs.close();
	ifs.close();
}

int minIndex(std::string *arr, int size)	//returns index of smallest element in array
{
	std::string smallest = arr[0];
	int index = 0;

	for (int i = 0; i < size; i++)
	{
		if (arr[i] < smallest && arr[i] != "")
		{
			smallest = arr[i];
			index = i;
		}
	}
	return index;
}

bool isEmptyArr(std::string *arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i] != "")
		{
			return false;
		}
	}
	return true;
}

std::fstream& goToLine(std::fstream& file, int num) {
	//Sets the seek pointer of file to the beginning of line num
	file.seekg(std::ios::beg);
	for (int i = 0; i < num - 1; i++) {
		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	return file;
}

template<typename E>
void initializeArr(E a[], int size) {	//Initiates array with value 0
	for (int i = 0; i < size; i++) {
		a[i] = 0;
	}
}