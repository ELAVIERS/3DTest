#pragma once

class Timer
{
	unsigned long long _frequency;
	unsigned long long _start;
public:
	Timer();
	~Timer() {};

	void Start();
	float Stop();
};
