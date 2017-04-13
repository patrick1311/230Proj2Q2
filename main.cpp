#include <iostream>
#include <fstream>
#include <string>
#include <chrono>	//time
#include "ReplacementSelection.cpp"
#include "heap.h"
#include "Comp.cpp"
//#include "heap.h"

void genRandFile();
void readData(std::string *buffer, int start, int size);
template<typename E> void printArr(E a[], int size);

int main()
{
	srand((unsigned)time(0));
	int size = 20;
	std::string *buffer = new std::string[size];
	std::string *heapArr = new std::string[size];

	genRandFile();
	readData(buffer, 0, size);
	heap<std::string, Comp<std::string>>* minHeap = new heap<std::string, Comp<std::string>>(heapArr, size, size);

	//heapArr = repSel<std::string>(buffer, minHeap, size);

	std::string wait;
	std::cin >> wait;	//Pause console after program finishes
	return 0;
}

void genRandFile()
{
	std::ofstream ofs;
	ofs.open("Random Data.txt");

	int randLines = (rand() % 100) + 20;
	int randLength, maxLength = 20;
	char randChar;
	for (int i = 0; i < randLines; i++)
	{
		randLength = (rand() % maxLength) + 1;
		for (int j = 0; j < randLength; j++)
		{
			randChar = (rand() % 94) + ' ';
			ofs << randChar;
		}
		ofs << std::endl;
	}
	ofs.close();
}

void readData(std::string *buffer, int start, int size)
{
	std::ifstream ifs("Random Data.txt");

	if (ifs.is_open())
	{
		ifs.seekg(start);
		//while(!stream.eof())
		for (int i = 0; i < size; i++)
		{
			//while (getline(ifs, buffer[i]))
			getline(ifs, buffer[i]);
		}
	}

	printArr(buffer, size);
	ifs.close();

	//delete buffer;
}

void writeData(std::string *buffer, int size)
{
	std::ofstream ofs("Sorted Data.txt");

	if (ofs.is_open())
	{
		//while(!stream.eof())
		for (int i = 0; i < size; i++)
		{
			//while (getline(ifs, buffer[i]))
			//getline(ofs, buffer[i]);
		}
	}

	printArr(buffer, size);
	ofs.close();

	//delete buffer;
}

template<typename E>
void printArr(E a[], int size) {	//Prints an array
	for (int i = 0; i < size; i++) {
		std::cout << a[i] << std::endl;
	}
}
