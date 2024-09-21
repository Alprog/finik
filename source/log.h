#pragma once

import std.compat;

void log_impl(std::string text);

template <typename... Args>
void log(std::format_string<Args...> fmt, Args&&... args)
{
    log_impl(std::format(fmt, std::forward<Args>(args)...));
}