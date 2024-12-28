export module byte_blob;

import core;

export class ByteBlob
{
public:
    ByteBlob(Path path);

    void* data() { return &str[0]; }
    size_t size() { return str.size(); };

    const std::string& asString() const { return str; }

private:
    std::string str;
};
