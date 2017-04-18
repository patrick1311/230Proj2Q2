// Heap class
template <typename E> class heap {
private:
	E* Heap;          // Pointer to the heap array
	int maxsize;         // Maximum size of the heap
	int n;               // Number of elements now in the heap

public:
	heap(E* h, int num, int max)     // Constructor
	{
		Heap = h;  n = num;  maxsize = max;  buildHeap();
	}
	int size() const       // Return current heap size
	{
		return n;
	}
	bool isLeaf(int pos) const // True if pos is a leaf
	{
		return (pos >= n / 2) && (pos < n);
	}
	int leftchild(int pos) const
	{
		return 2 * pos + 1;
	}    // Return leftchild position
	int rightchild(int pos) const
	{
		return 2 * pos + 2;
	}    // Return rightchild position
	int parent(int pos) const  // Return parent position
	{
		return (pos - 1) / 2;
	}
	inline void buildHeap()           // Heapify contents of Heap
	{
		for (int i = n / 2 - 1; i >= 0; i--) siftdown(i);
	}

	// Helper function to put element in its correct place
	inline void siftdown(int pos) {
		while (!isLeaf(pos)) { // Stop if pos is a leaf
			int j = leftchild(pos);  int rc = rightchild(pos);
			if ((rc < n) && Heap[rc] < Heap[j])
				j = rc;            // Set j to greater child's value
			if (Heap[pos] < Heap[j]) return; // Done
			E temp = Heap[pos];
			Heap[pos] = Heap[j];
			Heap[j] = temp;
			pos = j;             // Move down
		}
	}

	// Insert "it" into the heap
	inline void insert(const E& it) {
		int curr = n++;
		Heap[curr] = it;            // Start at end of heap
									// Now sift up until curr's parent > curr
		while ((curr != 0) && (Heap[curr] < Heap[parent(curr)])) {
			E temp = Heap[curr];
			Heap[curr] = Heap[parent(curr)];
			Heap[parent(curr)] = temp;
			curr = parent(curr);
		}
	}
	// Remove first value
	inline E removefirst() {
		E temp = Heap[0];	// Swap first with last value
		Heap[0] = Heap[--n];
		Heap[n] = temp;
		if (n != 0) siftdown(0);  // Siftdown new root val
		return Heap[n];             // Return deleted value
	}

	// Remove and return element at specified position
	inline E remove(int pos) {
		if (pos == (n - 1)) n--; // Last element, no work to do
		else
		{
			E temp = Heap[pos];	// Swap first with last value
			Heap[pos] = Heap[--n];
			Heap[n] = temp;
			while ((pos != 0) && (Heap[pos] < Heap[parent(pos)])) {
				E temp = Heap[pos];	 // Push up large key
				Heap[pos] = Heap[parent(pos)];
				Heap[parent(pos)] = temp;
				pos = parent(pos);
			}
			if (n != 0) siftdown(pos);     // Push down small key
		}
		return Heap[n];
	}

	inline E getVal(int pos) {
		return Heap[pos];
	}

	inline E* getValue(int pos) {
		return &Heap[pos];
	}

	inline void setVal(int pos, E val) {
		Heap[pos] = val;
	}

	inline void setHeapSize(int size)
	{
		n = size;
	}
};