//To do list: <-----------------LOOK HERE!
//1.get rid of global variables, (make class?)
//2.determine numRuns for multimerge
//3.test on larger sized buffers & heap; determine buffer/heap size
//4.answer prompt questions 
//5.clean up code: find more efficient/better methods, make code modular if possible, make coding style consistent, split functions into separate files? etc.
//6.write comments
//7.make beautiful graphs
//8.find fourth group member
//11.delete any unecessary testing code
//12.inline functions to speed up program
//13.speed up run

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
int eofLine = 10000;
int numRuns = 0;

inline void clearData(std::string fileName);
inline void genRandFile(std::string fileName, int lines);
inline std::string readData(std::ifstream& ifs, std::streamoff start);
inline std::streamoff readData(std::ifstream& ifs, std::string *inBuff, std::streamoff start, int size);
template<typename E> inline void writeData(std::ofstream& ofs, E output);
template<typename E> inline void writeData(std::ofstream& ofs, E *outBuff, int size);
template<typename E> inline void printArr(E a[], int size);
template<typename E> inline void repSel(std::string inFile, std::string outFile, heap<E, Comp<E>>* minHeap, std::streamoff start, int buffSize);
inline void multiMrg(std::string inFile, std::string outFile, int buffSize, int heapSize, int numRuns);
inline std::streamoff goToLine(std::ifstream& ifs, std::streamoff start, int lines);

int main()
{
	srand((unsigned)time(0));
	int fileSize = 100000, heapSize = eofLine, bufferSize = heapSize;
	std::string inputFile = "RandomData.txt", preMrgFile = "PreMerge.txt", mergeFile = "SortedData.txt";
	std::streamoff start = 0;
	std::string *heapArr = new std::string[heapSize];
	std::ifstream ifs(inputFile);
	std::ofstream ofs(preMrgFile, std::ios::out | std::ios::app);

	clearData(preMrgFile);	//Clear output file
	clearData(mergeFile);	//Clear output file
	std::cout << "Generating random file with " << fileSize << "records" << std::endl;
	genRandFile(inputFile, fileSize);	//Generate input file
	std::cout << "\t" << inputFile << " created" << std::endl;
	start = readData(ifs, heapArr, start, heapSize);	//Read data into heap array
		//std::cout << "start __________________" << start << std::endl;
	heap<std::string, Comp<std::string>>* minHeap = new heap<std::string, Comp<std::string>>(heapArr, heapSize, heapSize);
		//std::cout << "heap___________________________________" << std::endl;	//Delete when done testing
		//printArr(heapArr, heapSize);											//Delete when done testing
	std::cout << "Starting replacement selection" << std::endl;
	repSel<std::string>(inputFile, preMrgFile, minHeap, start, bufferSize);
	qsortO(heapArr, heapSize);
		//std::cout << "heap___________________________________" << std::endl;	//Delete when done testing
		//printArr(heapArr, heapSize);											//Delete when done testing
	writeData(ofs, heapArr, heapSize);	//Write array to output file
	std::cout << "\t" << preMrgFile << " created" << std::endl;
	std::cout << "Starting multiway merge" << std::endl;
	multiMrg(preMrgFile, mergeFile, bufferSize, heapSize, numRuns);	//Merge output buffers together
	std::cout << "\t" << mergeFile << " created" << std::endl;

	ifs.close();
	ofs.close();
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

	int randLength, maxLength = 12;
	char randChar;
	for (int i = 0; i < lines; i++)
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

inline std::string readData(std::ifstream& ifs, std::streamoff start)
{//Reads a line of data from file at line and returns the data
	std::string value;

	ifs.seekg(start);
	getline(ifs, value);
	return value;
}

inline std::streamoff readData(std::ifstream& ifs, std::string *inBuff, std::streamoff start, int size)
{	//Reads lines of data from file at position start and outputs position of seek pointer
	std::streamoff pos = 0;
	std::string eofTest;

	ifs.seekg(start);
	for (int i = 0; i < size; i++)
	{
		getline(ifs, inBuff[i]);
		if (ifs.eof())
		{
			eofLine = i;	//Record line number of eof
			done = true;
			break;	//Stop recording into input buffer
		}
	}
	pos = ifs.tellg();
	return pos;
}

template<typename E>
inline void writeData(std::ofstream& ofs, E output)
{	//Writes data to file
	ofs << output << std::endl;
}

template<typename E>
inline void writeData(std::ofstream& ofs, E *outBuff, int size)
{	//Writes array to file
	for (int i = 0; i < size; i++)
	{
		ofs << outBuff[i] << std::endl;
	}
}
/*
template<typename E>
inline void printArr(E a[], int size) {	//Prints an array	//Delete when done testing?
	for (int i = 0; i < size; i++) {
		std::cout << a[i] << std::endl;
	}
}*/

template<typename E>
inline void repSel(std::string inFile, std::string outFile, heap<E, Comp<E>>* minHeap, std::streamoff start, int buffSize)
{
	std::ifstream ifs(inFile);
	std::ofstream ofs(outFile, std::ios::out | std::ios::app);
	E *inBuff = new E[buffSize];
	E *outBuff = new E[buffSize];
	int heapSize = minHeap->size();

	do//for (int i = 0; i < 2; i++)
	{
		start = readData(ifs, inBuff, start, buffSize);
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
		writeData(ofs, outBuff, eofLine);	//Write output buffer to file

			//std::cout << "HeapSIZE______________________" << minHeap->size() << std::endl;
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
	ifs.close();
	ofs.close();
}

inline void multiMrg(std::string inFile, std::string outFile, int buffSize, int heapSize, int numRuns)	//Temporarily using quicksort for testing
{
	std::ifstream ifs(inFile);
	std::ofstream ofs(outFile, std::ios::out | std::ios::app);
	std::streamoff start = 0;
	std::string record;
	int size = numRuns + 1;
	Run<std::string> *runBuff = new Run<std::string>[size];

	for (int i = 0; i < size; i++)	//Build initial array of runs for heap
	{
		runBuff[i].setNum(i);	//Set run numbers
		runBuff[i].setPos(start);
		record = readData(ifs, start);	//Read record from file
		runBuff[i].setVal(record);	//Set run value
		if (i < (size - 2) || eofLine == 0)	//Set run size
		{
			runBuff[i].setSize(buffSize);
			start = goToLine(ifs, start, buffSize);
		}
		else if(i == (size - 2))
		{
			runBuff[i].setSize(eofLine);
			start = goToLine(ifs, start, eofLine);
		}
		else if(i == (size - 1))
		{
			runBuff[i].setSize(heapSize);
			start = goToLine(ifs, start, heapSize);
		}
	}
	heap<Run<std::string>, Comp<Run<std::string>>>* runHeap = 
		new heap<Run<std::string>, Comp<Run<std::string>>>(runBuff, size, size);	//Build heap of runs

	while (runHeap->size() != 0)	//Run until heap is empty
	{
		Run<std::string>* min = runHeap->getValue(0);	//Store pointer to heap root
		writeData(ofs, min->getVal());
			//std::cout << min->getVal() << std::endl;	//Delete when done testing
			//printHeap(runHeap, runHeap->size());			//Delete when done testing
			//std::cout << std::endl << std::endl;			//Delete when done testing
		min->incInd();	//Increase index of smallest run value
		start = goToLine(ifs, min->getPos(), 1);	//Set start to the position of the next line from the root's position
			//std::cout << "start: " << start << std::endl;
		min->setPos(start);	//Set root's position to start
		record = readData(ifs, start);	//Read record from file
		min->setVal(record);	//Set new value into run
		if (min->isDone())	//If run is done, remove run from heap and stop loop
		{
			runHeap->removefirst();
			if (runHeap->size() == 0)
			{
				break;
			}
		}
		runHeap->siftdown(0);
	}
	ifs.close();
	ofs.close();
	delete[] runBuff;
}

inline std::streamoff goToLine(std::ifstream& ifs, std::streamoff start, int lines) {
	//Sets the seek pointer of file to the beginning of line num
	std::streamoff pos; 
	ifs.seekg(start);
	for (int i = 0; i < lines; i++) {
		ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	pos = ifs.tellg();
	return pos;
}