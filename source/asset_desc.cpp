module asset_desc;

import texture;
import shader_source_file;

void AssetDesc::create_asset()
{
    auto extension = virtual_path.getExtension();

    if (extension == ".png")
    {
        loaded_asset = std::shared_ptr<Texture>();
    }
    else if (extension == ".inc" || extension == ".shader")
    {
        loaded_asset = std::shared_ptr<ShaderSourceFile>();
    }

    throw "unknown asset extension";
}