#include "log.h"

#include "Windows.h"
#include <format>

void log_impl(std::string text)
{
    OutputDebugStringA(text.c_str());
}