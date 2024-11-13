module;
#include "Windows.h"
module log;

import core;

void log_impl(std::string text)
{
    OutputDebugStringA(text.c_str());
}