#include "timer.h"

#include <chrono>

static uint64_t start_time = 0;

uint64_t get_microseconds() 
{
    auto duration = std::chrono::system_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
}

void set_start_time()
{
    start_time = get_microseconds();
}

uint64_t get_elapsed_time()
{
    return get_microseconds() - start_time;
}

std::string get_elapsed_time_string()
{
    std::string result = std::to_string(get_elapsed_time());

    if (result.size() > 6)
    {
        result.insert(result.size() - 6, 1, ' ');
        result.insert(result.size() - 3, 1, '\'');
    }

    return result;
}