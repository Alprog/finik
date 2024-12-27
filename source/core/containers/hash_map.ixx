export module containers:hash_map;

import std;
import primitive_types;

export template <typename TKey, typename TValue>
class HashMap
{
public:
    HashMap() = default;

    HashMap(std::initializer_list<std::pair<TKey, TValue>> list)
        : data{ list }
    {
    }

    const TValue& operator[](const TKey& key) const
    {
        return data[key];
    }
    
    TValue& operator[](const TKey& key)
    {
        return data[key];
    }

    auto begin() const
    {
        return data.begin();
    }

    auto begin()
    {
        return data.begin();
    }

    bool contains(const TKey& key) const
    {
        return data.contains(key);
    }

    int32 count() const
    {
        return data.size();
    }

    void clear()
    {
        data.clear();
    }

    bool empty() const
    {
        return data.empty();
    }

    auto end() const
    {
        return data.end();
    }

    auto end()
    {
        return data.end();
    }

    auto find(const TKey& key) const
    {
        return data.find(key);
    }

    auto find(const TKey& key)
    {
        return data.find(key);
    }

    bool remove(const TKey& key)
    {
        return data.erase(key) > 0;
    }

private:
    std::unordered_map<TKey, TValue> data;
};