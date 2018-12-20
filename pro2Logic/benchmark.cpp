#include "benchmark.h"

Benchmark *Benchmark::mInstance	=	0;

Benchmark *Benchmark::Instance()
{
	if(mInstance)
		return mInstance;
	return mInstance = new Benchmark;
}

void Benchmark::Destroy()
{
	if(mInstance)
		delete mInstance;
}

Benchmark::Benchmark():mDTime(0)
{
	mLastTime = (UINT64)timeGetTime();
}

Benchmark::~Benchmark(){}

void Benchmark::operator()()
{
	UINT64 ticks = (UINT64)timeGetTime();

	mDTime = ticks - mLastTime;

	mLastTime = ticks;
}
