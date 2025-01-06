export module containers:string;

import std;
import primitive_types;

export class String
{
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

    char& operator[](size_t index)
    {
        return data[index];
    }

    const char& operator[](size_t index) const
    {
        return data[index];
    }

    auto begin() const
    {
        return data.begin();
    }

    auto begin()
    {
        return data.begin();
    }

    auto end() const
    {
        return data.end();
    }

    auto end()
    {
        return data.end();
    }

private:
    std::string data;
};
