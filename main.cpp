//To do list: <-----------------LOOK HERE!
//1.get rid of global variables, (make class?)
//2.determine numRuns for multimerge
//3.test on larger sized buffers & heap; determine buffer/heap size
//4.answer prompt questions 
//5.clean up code: find more efficient/better methods, make code modular if possible, make coding style consistent, split functions into separate files? etc.
//6.write comments
//7.make beautiful graphs
//8.find fourth group member
//9.change readData to void and use goToLine for start?
//10.change ZZZZZZZZZ looks ghetto as fuck
//11.delete any unecessary testing code
//12.inline functions to speed up program

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>	//time
#include <limits>	//GoToLine
#include "heap.h"
#include "Run.cpp"
#include "Comp.cpp"
#include "qsortop.cpp"


int THRESHOLD2 = 8;
bool done = false;
int eofLine = 7;
int numRuns = 0;


inline void clearData(std::string fileName);
inline void genRandFile(std::string fileName, int lines);
inline int calcLineNum(int buffSize, int numRuns);
inline std::streamoff readData(std::string fileName, std::string *inBuff, std::streamoff start, int size);
template<typename E> inline void writeData(std::string fileName, E output);
template<typename E> inline void writeData(std::string fileName, E *outBuff, int size);
template<typename E> inline void printArr(E a[], int size);
template<typename E> inline void repSel(std::string inFile, std::string outFile, heap<E, Comp<E>>* minHeap, std::streamoff start, int buffSize);
inline void multiMrg(std::string inFile, std::string outFile, int buffSize, int numRuns);
template<typename E> inline void initializeArr(E a[], int size);	//Initiates array with value 0
inline std::fstream& goToLine(std::fstream& file, int num);
inline int minIndex(std::string *arr, int size);	//Returns index of smallest element in array
inline bool isEmptyArr(std::string *arr, int size);

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
	//std::cout << "heap___________________________________" << std::endl;	//Delete when done testing
	//printArr(heapArr, heapSize);											//Delete when done testing
	repSel<std::string>(inputFile, preMrgFile, minHeap, start, bufferSize);
	qsortO(heapArr, heapSize);
	//std::cout << "heap___________________________________" << std::endl;	//Delete when done testing
	//printArr(heapArr, heapSize);											//Delete when done testing
	writeData(preMrgFile, heapArr, heapSize);	//Write array to output file
	multiMrg(preMrgFile, mergeFile, bufferSize, numRuns);	//Merge output buffers together
	std::cout << "Finished" << std::endl;
	std::string wait;
	std::cin >> wait;	//Pause console after program finishes
	return 0;
}

inline void clearData(std::string fileName)
{	//Clears file
	std::ofstream ofs(fileName, std::ios::out | std::ios::trunc);
	ofs.close();
}

inline void genRandFile(std::string fileName, int lines)
{	//Generates random character text file
	std::ofstream ofs;
	ofs.open(fileName);

	int randLines = lines;//(rand() % 100) + 60;
	int randLength, maxLength = 12;
	char randChar;
	for (int i = 0; i < randLines; i++)
	{
		randLength = (rand() % maxLength) + 8;
		for (int j = 0; j < randLength; j++)
		{
			randChar = (rand() % 26) + 'A';
			ofs << randChar;
		}
		ofs << std::endl;
	}
	ofs.close();
}

inline std::streamoff readData(std::string fileName, std::string *inBuff, std::streamoff start, int size)
{	//Reads lines of data from file at position start and outputs position of seek pointer
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

template<typename E>
inline void writeData(std::string fileName, E output)
{	//Writes data to file
	std::ofstream ofs(fileName, std::ios::out | std::ios::app);

	if (ofs.is_open())
	{
		ofs << output << std::endl;
	}
	ofs.close();
}

template<typename E>
inline void writeData(std::string fileName, E *outBuff, int size)
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
inline void printArr(E a[], int size) {	//Prints an array	//Delete when done testing?
	for (int i = 0; i < size; i++) {
		std::cout << a[i] << std::endl;
	}
}

template<typename E>
inline void repSel(std::string inFile, std::string outFile, heap<E, Comp<E>>* minHeap, std::streamoff start, int buffSize)
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
		//std::cout << "in___________________________________" << std::endl;		  //Delete when done testing
		//printArr(inBuff, buffSize);												  //Delete when done testing
		//std::cout << "out___________________________________" << std::endl;		  //Delete when done testing
		//printArr(outBuff, eofLine);												  //Delete when done testing
		if (eofLine != 0)
		{
			numRuns++;
		}
	} while (!done);
	//std::cout << numRuns << "numRuns___________________________________" << std::endl;		//Delete when done testing
	delete[] inBuff;
	delete[] outBuff;
}

inline void multiMrg(std::string inFile, std::string outFile, int buffSize, int numRuns)	//Temporarily using quicksort for testing
{
	std::string record;
	std::fstream ifs(inFile);
	std::ofstream ofs(outFile);
	int size = numRuns + 1;
	int line = calcLineNum(buffSize, numRuns);
	Run<std::string> *runBuff = new Run<std::string>[size];
	if (ifs.is_open() && ofs.is_open())
	{
		for(int i = 0; i < size; i++)
		{ 
			goToLine(ifs, buffSize * i + 1);
			runBuff[i].setNum(i);
			if (i < (size - 1))
			{
				runBuff[i].setSize(buffSize);
			}
			else
			{
				runBuff[i].setSize(eofLine);
			}
			ifs >> record;
			std::cout << record << std::endl;
			runBuff[i].setValue(record);
		}
		heap<Run<std::string>, Comp<Run<std::string>>>* runHeap = new heap<Run<std::string>, Comp<Run<std::string>>>(runBuff, size, size);

		do
		{
			//std::cout << "_____________________" << std::endl;		//Delete when done testing
			Run<std::string> *min = &runHeap->getVal(0);
			writeData(outFile,runHeap->getVal(0).getValue());
			std::cout << runHeap->getVal(0).getValue() << std::endl;
			runHeap->getVal(0).incIndex();
			if (runHeap->getVal(0).isDone())
			{
				runHeap->removefirst();
			}
			goToLine(ifs, buffSize*runHeap->getVal(0).getNum() + runHeap->getVal(0).getInd() + 1);
			ifs >> record;
			runHeap->getVal(0).setValue(record);
			runHeap->siftdown(0);
		} while (runHeap->size()!= 0);	//Continue looping until all runs are finished
	}
	ofs.close();
	ifs.close();
	delete[] runBuff;
}

inline int calcLineNum(int buffSize, int numRuns)
{
	return buffSize * numRuns - (buffSize + eofLine);
}

template<typename E>
inline void initializeArr(E a[], int size) {	//Initiates array with value 0
	for (int i = 0; i < size; i++) {
		a[i] = 0;
	}
}

inline std::fstream& goToLine(std::fstream& file, int num) {
	//Sets the seek pointer of file to the beginning of line num
	file.seekg(std::ios::beg);
	for (int i = 0; i < num - 1; i++) {
		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	return file;
}

inline int returnLineNum(std::fstream& file, std::string str)
{

}

inline int minIndex(std::string *arr, int size)	//returns index of smallest element in array
{
	std::string smallest = "ZZZZZZZZZZZZZZZZZ";
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

inline bool isEmptyArr(std::string *arr, int size)
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
