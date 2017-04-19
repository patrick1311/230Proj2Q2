class ReadData 
{
private:
	bool done;
	int eofLine;
	int numRuns;
	std::streamoff pos;
public:
	ReadData(){}
	ReadData(int line)
	{
		eofLine = line;
		pos = 0;
		done = false;
		numRuns = 0;
	}
	inline void Done()
	{
		done = true;
	}
	inline bool isDone()
	{
		return done;
	}
	inline int getEofLine()
	{
		return eofLine;
	}
	inline void setEofLine(int s)
	{
		eofLine = s;
	}
	inline void setPos(std::streamoff n)
	{
		pos = n;
	}
	inline std::streamoff getPos()
	{
		return pos;
	}
	inline void incRuns()
	{
		numRuns++;
	}
	inline int getRuns()
	{
		return numRuns;
	}
};

