export module shader_source_file;

import core;
import asset;

export class ShaderSourceFile : public Asset
{
public:
    using Asset::Asset;

    void HotReload(Blob& blob) override
    {
        sourceText = blob.asString();
        version++;
    }

    const std::string& GetSourceText() const
    {
        return sourceText;
    }

private:
    std::string sourceText;
};