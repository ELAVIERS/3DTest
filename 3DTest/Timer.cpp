#include "Timer.h"

#include <Windows.h>

inline unsigned long long GetClock() {
	static LARGE_INTEGER value;
	::QueryPerformanceCounter(&value);
	return value.QuadPart;
}

Timer::Timer() {
	LARGE_INTEGER read_val;
	::QueryPerformanceFrequency(&read_val);
	_frequency = read_val.QuadPart;
}

void Timer::Start() {
	_start = GetClock();
}

float Timer::Stop() {
	return (float)(GetClock() - _start) / (float)_frequency;
}
