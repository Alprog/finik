export module timer;

import core;

export
{
    void initTimer();
    uint64 getTimestamp();
    uint64 toMicroseconds(uint64 timestamp);
    uint64 getMicroseconds();

    uint64 get_elapsed_time();
}