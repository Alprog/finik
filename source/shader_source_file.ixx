export module shader_source_file;

import core;
import asset;

export class ShaderSourceFile : public Asset
{
public:
    using Asset::Asset;

    const std::string& GetSourceText() const
    {
        return sourceText;
    }

protected:
    void hot_reload(ByteBlob& blob) override
    {
        sourceText = blob.asString();
    }

private:
    std::string sourceText;
};