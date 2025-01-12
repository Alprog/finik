export module texture;

import core;
import dx;
import descriptor_handle;
import images;
import gpu_resource;
import byte_blob;
import asset;
import asset_path;

export class Texture : public GpuResource, public Asset
{
public:
    Texture(AssetPath asset_path);

    void resize(int32 width, int32 height);

    Texture(int32 width, int32 height);
    Texture(Image& image);

    void setData(Image& image);

protected:
    void hot_reload(ByteBlob& blob) override;

private:
    int32 calcMipMapCount();

public:
    int Width;
    int Height;

    D3D12_RESOURCE_STATES state;

    DescriptorHandle descriptorHandle;
};
