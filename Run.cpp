// Heap class
template <typename E> class Run {
private:
	int index;
	E value;

public:
	Run(int runIndex, E runValue)     // Constructor
	{
		index = runIndex;
		value = runValue;
	}
};