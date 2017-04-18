#include <fstream>
// Run class
template <typename E> class Run {
private:
	int index;	//Index of record in run
	int size;	//Number of records in run
	E value;	//Value of record at index number
	std::streamoff position;	//Position of record in file

public:
	Run() { index = 0; }
	Run(int ind, int s, E val, std::streamoff pos)     // Constructor
	{
		index = ind;
		size = s;
		value = val;
		position = pos;
	}
	inline int getInd()
	{
		return index;
	}
	inline E getVal()
	{
		return value;
	}
	inline std::streamoff getPos()
	{
		return position;
	}
	inline void incInd()
	{
		index++;
	}
	inline void setSize(int n)
	{
		size = n;
	}
	inline void setVal(E n)
	{
		value = n;
	}
	inline void setPos(std::streamoff pos)
	{
		position = pos;
	}
	inline bool isDone()
	{
		return index == size;
	}
	inline bool operator<(const Run &R2)
	{
		return value < R2.value;
	}
	/*
	void print()
	{
		//std::cout << "Num: " << num << std::endl;
		std::cout << "Index: " << index << std::endl;
		std::cout << "Size: " << size << std::endl;
		std::cout << "Value: " << value << std::endl;
		std::cout << "Pos: " << position << std::endl;
		std::cout << std::endl;
	}*/
};