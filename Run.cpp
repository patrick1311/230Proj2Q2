// Heap class
template <typename E> class Run {
private:
	int num;
	int index;
	int size;
	E value;

public:
	Run() { index = 0;}
	Run(int n, E val)     // Constructor
	{
		num = n;
		value = val;
	}
	inline int getNum()
	{
		return num;
	}
	inline int getInd()
	{
		return index;
	}
	inline E getValue()
	{
		return value;
	}
	inline void setNum(int n)
	{
		num = n;
	}
	inline void setValue(E n)
	{
		value = n;
	}
	inline void setSize(int n)
	{
		size = n;
	}
	inline void incIndex()
	{
		index++;
	}
	inline bool isDone()
	{
		return index == size;
	}

	bool operator<(const Run &R2)
	{
		return value < R2.value;
	}

	void print()
	{
		std::cout << "Num: " << num <<std::endl;
		std::cout << "Index: " << index << std::endl;
		std::cout << "Size: " << size << std::endl;
		std::cout << "Value: " << value << std::endl;
		std::cout << std::endl;
	}
};