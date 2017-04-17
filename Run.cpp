// Heap class
template <typename E> class Run {
private:
	int num;
	int index;
	int size;
	E value;

public:
	Run() { index = 0; }
	Run(int n, E val, int index = 0)     // Constructor
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
		val = n;
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
		if (index == size)
		{
			return true;
		}
		return false;
	}

	bool operator<(const Run &R2)
	{
		return value < R2.value;
	}
};