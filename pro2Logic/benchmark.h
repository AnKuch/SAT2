#ifndef BENCHMARK_H_INCLUDED
#define BENCHMARK_H_INCLUDED
//#pragma comment (lib,"Winmm.lib")


#include <ctime>

class Benchmark
{
public:
	static Benchmark*	Instance();
	static void	Destroy();

	void operator()();
	UINT64 GetDTime(){return mDTime;}

private:
	Benchmark();
	~Benchmark();

	static Benchmark *mInstance;
	UINT64 mLastTime;
	UINT64 mDTime;
};


#endif // BENCHMARK_H_INCLUDED
