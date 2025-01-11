export module model;

import core;
import asset;
import obj_loader;
import mesh;

export class Model : public Asset
{
    using Asset::Asset;

    void hot_reload(ByteBlob &blob) override
    {
        ObjLoader loader;
        loader.load(blob.asString());
    }

    Mesh mesh;
};