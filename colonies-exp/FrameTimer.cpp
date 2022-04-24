#include "FrameTimer.h"

using namespace std::chrono;

FrameTimer::FrameTimer()
{
	last = steady_clock::now();
}

float FrameTimer::Mark()
{
	const auto temp = last;
	last = steady_clock::now();
	const duration<float> frameTime = last - temp;
	return frameTime.count();
}