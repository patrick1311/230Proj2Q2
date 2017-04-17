template <typename E> class Comp {
private:
	int a, b;
public:
	inline bool static prior(E a, E b)
	{
		return a < b;	//min comp
	}
};