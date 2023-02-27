#pragma once
#include <ratio>
#include <chrono>
#include <string>
#include <windows.h>

class CHTime
{
public:
	void pt();
	void pt(const char* tag);
	std::string gt();
	int64_t getTImeMicros();
private:
	std::time_t getTimeStamp();
	std::tm* gettm(std::time_t timestamp);
};

void test();

