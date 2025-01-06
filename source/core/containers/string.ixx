export module containers:string;

import std;
import primitive_types;
import :array;

export class String
{
public:
    String() = default;

    String(const char* c_string)
        : data{ c_string }
    {        
    }

    String(const std::string& string)
        : data{ string }
    {
    }

    String(std::string&& string)
        : data{ std::move(string) }
    {
    }

    String(std::initializer_list<char> list)
        : data{ list }
    {
    }

    String(int32 length)
        : data(length, 0)
    {
    }

    char& operator[](size_t index)
    {
        return data[index];
    }

    const char& operator[](size_t index) const
    {
        return data[index];
    }

    auto operator<=>(const String& other) const = default;

    auto begin() const
    {
        return data.begin();
    }

    auto begin()
    {
        return data.begin();
    }

    static bool caseInsensitiveCompare(const String& lhs, const String& rhs)
    {
        return lhs.lowerCase() == rhs.lowerCase();
    }

    int32 count() const
    {
        return data.size();
    }

    auto end() const
    {
        return data.end();
    }

    auto end()
    {
        return data.end();
    }

    bool endsWith(const String& pattern)
    {
        auto stringLength = length();
        auto patternLength = pattern.length();
        if (stringLength >= patternLength)
        {
            return substr(stringLength - patternLength, patternLength) == pattern;
        }
        return false;
    }

    int32 length() const
    {
        return data.size();
    }

    String lowerCase() const
    {
        String result(data.size());
        std::transform(data.begin(), data.end(), result.begin(), [](char c) { return std::tolower(c); });
        return result;
    }

    void reserve(int32 capacity)
    {
        data.reserve(capacity);
    }

    void resize(int32 new_count)
    {
        data.resize(new_count);
    }

    bool startsWith(const String& pattern)
    {
        return substr(0, pattern.count()) == pattern;
    }

    String substr(int32 startIndex, int32 count)
    {
        return data.substr(startIndex, count);
    }

    String upperCase() const
    {
        String result(data.size());
        std::transform(data.begin(), data.end(), result.begin(), [](char c) { return std::toupper(c); });
        return result;
    }

private:
    std::string data;
};
