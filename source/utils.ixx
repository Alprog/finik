export module utils;

import std;

export
{
    std::vector<std::string> split(std::string string, std::string separator);
    std::string join(std::vector<std::string> vector, std::string separator);

    void replace(std::string& string, std::string oldValue, std::string newValue);
    std::string getReplaced(std::string string, std::string oldValue, std::string newValue);

    std::string lowerCase(std::string string);
    std::string upperCase(std::string string);
    bool caseInsensitiveCompare(const std::string& string1, const std::string& string2);

    bool startsWith(const std::string& string, const std::string& pattern);
    bool endsWith(const std::string& string, const std::string& pattern);

    std::string toStr(std::wstring wstr);
    std::wstring toWStr(std::string str);

    float lerp(float a, float b, float k);

    template <typename CT, typename T>
    bool contains(CT container, T item)
    {
        return std::find(std::begin(container), std::end(container), item) != std::end(container);
    }
}

