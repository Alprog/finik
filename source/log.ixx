export module log;

import core;

export void log_impl(std::string text);

export template <typename... Args>
void log(std::format_string<Args...> fmt, Args&&... args)
{
    log_impl(std::format(fmt, std::forward<Args>(args)...));
}