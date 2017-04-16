// Heap class
template <typename E> class Run {
private:
	int index;
	E value;

public:
	Run(int ind, E val)     // Constructor
	{
		index = ind;
		value = val;
	}
	inline int getIndex()
	{
		return index;
	}
	inline E getValue()
	{
		return value;
	}
};