#include "log.h"

#include "Windows.h"
import std.compat;

void log_impl(std::string text)
{
    OutputDebugStringA(text.c_str());
}