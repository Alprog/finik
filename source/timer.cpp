#include "timer.h"

#include <Windows.h>

import std.compat;

uint64_t startTimestamp;
uint64_t cpuFrequency;
uint64_t gpuFrequency;
uint64_t cpuTicksInMicrosecond;

void initTimer()
{
    startTimestamp = getTimestamp();
    QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&cpuFrequency));
    cpuTicksInMicrosecond = cpuFrequency / 1'000'000;
}

uint64_t getTimestamp()
{
    uint64_t result;
    QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&result));
    return result;
}

uint64_t get_elapsed_time()
{
    return (getTimestamp() - startTimestamp) / cpuTicksInMicrosecond;
}

uint64_t getMicroseconds()
{
    return getTimestamp() / cpuTicksInMicrosecond;
}

uint64_t toMicroseconds(uint64_t timestamp)
{
    return timestamp / cpuTicksInMicrosecond;
}