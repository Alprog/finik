export module timebox;

import std.compat;

export namespace finik::profiler
{
    struct Timebox
    {
        Timebox(const char* label, uint8_t level);
        void end();

        const char* label;
        uint64_t startTimestamp;
        uint64_t endTimestamp;
        uint8_t level;
    };

    static_assert(sizeof(Timebox) == 32);
}
