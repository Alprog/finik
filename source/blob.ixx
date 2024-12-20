export module blob;

import core;

export class Blob
{
public:
    Blob(Path path);

    void* data() { return &str[0]; }
    size_t size() { return str.size(); };

    const std::string& asString() const { return str; }

private:
    std::string str;
};
