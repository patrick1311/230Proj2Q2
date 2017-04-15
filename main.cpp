#include <iostream>
#include <fstream>
#include <string>
#include <chrono>	//time
#include <limits>	//GoToLine
//#include "ReplacementSelection.cpp"
#include "heap.h"
#include "Comp.cpp"
#include "heap.h"
#include "qsortop.cpp"
//#pragma once

int THRESHOLD2 = 8;
bool done = false;
int eofLine = 7;

void genRandFile(std::string fileName, int lines);
void genRandFile2(std::string fileName, int lines);
template<typename E> void fillArrAsc(E a[], int size);
template<typename E> void shuffleArr(E a[], int size);
std::streamoff readData(std::string fileName, std::string *inBuff, std::streamoff start, int size);
template<typename E> void printArr(E a[], int size);
template<typename E> void printHeap(heap<E, Comp<E>>* heap, int size);
template<typename E> void repSel(std::string inFile , std::string outFile, heap<E, Comp<E>>* minHeap, std::streamoff start, int buffSize);
void clearData(std::string fileName);
template<typename E> void writeData(std::string fileName, E *outBuff, int size);
void multiMrg(std::string inFile, std::string outFile, int buffSize, int numRuns);
std::fstream& goToLine(std::fstream& file, int num);
template<typename E> void initializeArr(E a[], int size);	//Initiates array with value 0

int main()
{
	srand((unsigned)time(0));
	int bufferSize = eofLine, heapSize = 7;
	std::streamoff start;
	std::string inputFile = "RandomData.txt", outputFile = "SortedData.txt";

	std::string *heapArr = new std::string[heapSize];
	clearData(outputFile);	//clear output file
	genRandFile(inputFile, heapSize + (bufferSize *3) + 4);	//generate input file
	start = readData(inputFile, heapArr, 0, heapSize);	//read data into heap array
	heap<std::string, Comp<std::string>>* minHeap = new heap<std::string, Comp<std::string>>(heapArr, heapSize, heapSize);
		std::cout << "heap___________________________________" << std::endl;
		printArr(heapArr, heapSize);
	repSel<std::string>(inputFile, outputFile, minHeap, start, bufferSize);
	qsortO(heapArr, heapSize);
		std::cout << "heap___________________________________" << std::endl;
		printArr(heapArr, heapSize);
	writeData(outputFile, heapArr, heapSize);	//write array to output file
	//multiMrg<std::string>(outputFile, heapSize + (bufferSize + 2));

	std::string wait;
	std::cin >> wait;	//Pause console after program finishes
	return 0;
}

void genRandFile(std::string fileName, int lines)
{
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

void genRandFile2(std::string fileName, int lines)
{
	std::ofstream ofs;
	ofs.open(fileName);

	std::string *stringArr = new std::string[lines];
	fillArrAsc(stringArr, lines);
	shuffleArr(stringArr, lines);

	for (int i = 0; i < lines; i++)
	{
		ofs << stringArr[i] << std::endl;
	}
	ofs.close();
	delete[] stringArr;
}

template<typename E>
void fillArrAsc(E a[], int size) {	//Fills array with values 0-n in ascending order
	for (int i = 0; i < size; i++) {
		a[i] = i + 65;
	}
}

template<typename E>
void shuffleArr(E a[], int size) {	//Randomly shuffles an array
	int num;
	for (int i = 0; i < size; i++) {
		num = rand() % size;
		swap(a[i], a[num]);
	}
}

std::streamoff readData(std::string fileName, std::string *inBuff, std::streamoff start, int size)
{
	std::streamoff getPos;
	std::ifstream ifs(fileName);

	if (ifs.is_open())
	{
		ifs.seekg(start);
		//while(!stream.eof())
		for (int i = 0; i < size; i++)
		{
			if (ifs.eof())
			{
				eofLine = i - 1;	//record line number of eof
				std::cout << "line number is: " << eofLine << std::endl;
				done = true;
				break;	//stop recording into input buffer
			}
			//while (getline(ifs, buffer[i]))
			getline(ifs, inBuff[i]);
		}
	}
	getPos = ifs.tellg();
	//printArr(inBuff, size);
	ifs.close();

	return getPos;
	//delete buffer;
}

void clearData(std::string fileName)
{
	std::ofstream ofs(fileName, std::ios::out | std::ios::trunc);
	ofs.close();
}

template<typename E>
void writeData(std::string fileName, E *outBuff, int size)
{
	std::ofstream ofs(fileName, std::ios::out | std::ios::app);

	if (ofs.is_open())
	{
		//ofs.seekp(start);
		//while(!stream.eof())
		for (int i = 0; i < size; i++)
		{
			//while (getline(ifs, buffer[i]))
			ofs << outBuff[i] << std::endl;
		}
	}
	//printArr(outBuff, size);
	ofs.close();
}

template<typename E>
void printArr(E a[], int size) {	//Prints an array
	for (int i = 0; i < size; i++) {
		std::cout << a[i] << std::endl;
	}
}

template<typename E>
void printHeap(heap<E, Comp<E>>* heap, int size) {	//Prints a heap
	for (int i = 0; i < size; i++) {
		std::cout << heap->getVal(i) << std::endl;
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
		//std::cout << "start" << start << std::endl;
		start = readData(inFile, inBuff, start, buffSize);
		//std::cout << "start" << start << std::endl;
		for (int j = 0; j < eofLine; j++)
		{
			if (minHeap->size() == 0)	//if heap size is 0, rebuild heap
			{
				minHeap->setHeapSize(heapSize);
				minHeap->buildHeap();
				//std::cout << minHeap->size() << "buildHeap_______________________" << std::endl;
			}

			outBuff[j] = minHeap->getVal(0);	//send root to heap buffer
			minHeap->setVal(0, inBuff[j]);
			if (inBuff[j] > outBuff[j])
			{
				minHeap->siftdown(0);	//siftdown root
				//std::cout << minHeap->size() << "size_______________________" << std::endl;

			}
			else
			{
				minHeap->removefirst();
				//std::cout << minHeap->size() << "size_______________________" << std::endl;
			}
		}

		writeData(outFile, outBuff, eofLine);

		std::cout << "in___________________________________" << std::endl;
		printArr(inBuff, buffSize);
		std::cout << "out___________________________________" << std::endl;
		printArr(outBuff, eofLine);

		minHeap->setHeapSize(heapSize);
		minHeap->buildHeap();
		//std::cout << minHeap->size() << "buildHeap_______________________" << std::endl;
	} while (!done);
	delete[] inBuff;
	delete[] outBuff;
}

template<typename E>
void multiMrg(std::string inFile, std::string outFile, int buffSize, int numRuns)	//Temporarily using quicksort for testing
{
	std::ifstream ifs(inFile);
	//std::ifstream ofs(outFile);
	int size = numRuns + 1, minIndex;
	E *runBuff = new E[size];
	E runStart = new E[size];
	initializeArr(runStart, numRuns + 1);
	
	if (ifs.is_open())
	{
		for (int i = 0; i < size; i++)	//store values from each run into array
		{
			runBuff[i] = firstElement(inFile, i + 1, runStart[i], buffSize);
		}
		minIndex = minIndex(runBuff, size);
		//write smallest value to file
		writeData(outFile, runBuff[minIndex], 1);
		runStart[minIndex]++;

	}

	/*
	readData(fileName, inBuff, 0, buffSize);

	qsortO(inBuff, buffSize);

	clearData(fileName);
	writeData(fileName, inBuff, buffSize);*/

	delete[] runBuff;
	ifs.close();
}

template<typename E>
E firstElement(std::string fileName, int run, int start, int buffSize)//returns first element of run
{
	std::ifstream ifs(fileName);
	E first;
	if (ifs.is_open())
	{
		goToLine(ifs, buffSize * run + start);
		getline(ifs, first);
	}
	ifs.close();
	return first;
}

template<typename E>
int minIndex(E arr[], int size)	//returns index of smallest element in array
{
	E smallest = arr[0];
	int index = 0;

	for (int i = 1; i < size; i++)
	{
		if (arr[i] < smallest)
		{
			smallest = arr[i];
			index = i;
		}
	}
	return index;
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