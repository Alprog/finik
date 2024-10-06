module;
#include <cstdint>
export module timer;

import std;

export
{
    void initTimer();
    uint64_t getTimestamp();
    uint64_t toMicroseconds(uint64_t timestamp);
    uint64_t getMicroseconds();

    uint64_t get_elapsed_time();
}